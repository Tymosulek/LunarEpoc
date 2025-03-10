/*******************************************************************************
The content of this file includes portions of the proprietary AUDIOKINETIC Wwise
Technology released in source code form as part of the game integration package.
The content of this file may not be used without valid licenses to the
AUDIOKINETIC Wwise Technology.
Note that the use of the game engine is subject to the Unreal(R) Engine End User
License Agreement at https://www.unrealengine.com/en-US/eula/unreal
 
License Usage
 
Licensees holding valid licenses to the AUDIOKINETIC Wwise Technology may use
this file in accordance with the end user license agreement provided with the
software or, alternatively, in accordance with the terms contained
in a written agreement between you and Audiokinetic Inc.
Copyright (c) 2024 Audiokinetic Inc.
*******************************************************************************/

#pragma once

#include "WwiseUnrealDefines.h"
#include "Wwise/Stats/NamedEvents.h"

#if UE_5_1_OR_LATER
#include "Tasks/Task.h"
#include "Async/Async.h"
#else
#include "Async/TaskGraphInterfaces.h"
#endif

/// Adaptor on UE::Tasks::ETaskPriority ENamedThreads::Type, with additional GameThread
#if UE_5_1_OR_LATER
enum class EWwiseTaskPriority : int8
{
	High = static_cast<int8>(UE::Tasks::ETaskPriority::High),
	Normal = static_cast<int8>(UE::Tasks::ETaskPriority::Normal),
	Default = static_cast<int8>(UE::Tasks::ETaskPriority::Default),
	BackgroundHigh = static_cast<int8>(UE::Tasks::ETaskPriority::BackgroundHigh),
	BackgroundNormal = static_cast<int8>(UE::Tasks::ETaskPriority::BackgroundNormal),
	BackgroundLow = static_cast<int8>(UE::Tasks::ETaskPriority::BackgroundLow),
	GameThread = static_cast<int8>(-1)
};
#else
enum class EWwiseTaskPriority : int32
{
	High = ENamedThreads::AnyHiPriThreadNormalTask,
	Normal = ENamedThreads::AnyNormalThreadNormalTask,
	Default = EWwiseTaskPriority::Normal,
	BackgroundHigh = ENamedThreads::AnyBackgroundHiPriTask,
	BackgroundNormal = ENamedThreads::AnyBackgroundThreadNormalTask,
	BackgroundLow = ENamedThreads::AnyBackgroundThreadNormalTask,
	GameThread = ENamedThreads::GameThread
};
#endif

/// Adaptor on UE::Tasks::ETaskFlags
#if UE_5_4_OR_LATER
using EWwiseTaskFlags = UE::Tasks::ETaskFlags;
#else
enum class EWwiseTaskFlags
{
	None,
	DoNotRunInsideBusyWait // Ignored: do not pick this task for busy-waiting
};
#endif

#if !UE_5_1_OR_LATER
// Adaptor for missing SCOPED_NAMED_EVENT_TCHAR_CONDITIONAL in UE4.27 and UE5.0. Equivalent to HAL/PlatformMisc.h and ProfilingDebugging/CpuProfilerTrace.h from UE5.3.
#if ENABLE_NAMED_EVENTS
class FWwiseScopedNamedEventConditional
{
public:
	FWwiseScopedNamedEventConditional(const struct FColor& Color, const TCHAR* Text, bool bCondition)
		: bStarted(bCondition)
	{
		if (bCondition)
		{
			FPlatformMisc::BeginNamedEvent(Color, Text);
		}
	}

	FWwiseScopedNamedEventConditional(const struct FColor& Color, const ANSICHAR* Text, bool bCondition)
		: bStarted(bCondition)
	{
		if (bCondition)
		{
			FPlatformMisc::BeginNamedEvent(Color, Text);
		}
	}

	~FWwiseScopedNamedEventConditional()
	{
		if (bStarted)
		{
			FPlatformMisc::EndNamedEvent();
		}
	}

private:
	bool bStarted;
};
#endif

#if CPUPROFILERTRACE_ENABLED
struct FWwiseDynamicEventScope
{
	FORCEINLINE FWwiseDynamicEventScope(const ANSICHAR* InEventName, bool bInCondition, const ANSICHAR* InFile = nullptr, uint32 InLine = 0)
		: bEnabled(bInCondition && CpuChannel)
	{
		if (bEnabled)
		{
			FCpuProfilerTrace::OutputBeginDynamicEvent(InEventName);
		}
	}

	FORCEINLINE FWwiseDynamicEventScope(const TCHAR* InEventName, bool bInCondition, const ANSICHAR* InFile = nullptr, uint32 InLine = 0)
		: bEnabled(bInCondition && CpuChannel)
	{
		if (bEnabled)
		{
			FCpuProfilerTrace::OutputBeginDynamicEvent(InEventName);
		}
	}

	FORCEINLINE ~FWwiseDynamicEventScope()
	{
		if (bEnabled)
		{
			FCpuProfilerTrace::OutputEndEvent();
		}
	}

	bool bEnabled;
};

#define TRACE_CPUPROFILER_EVENT_SCOPE_TEXT_CONDITIONAL(Name, Condition) \
	FWwiseDynamicEventScope PREPROCESSOR_JOIN(__CpuProfilerEventScope, __LINE__)(Name, (Condition), __FILE__, __LINE__);
#else
#define TRACE_CPUPROFILER_EVENT_SCOPE_TEXT_CONDITIONAL(Name, Condition)
#endif

#if ENABLE_NAMED_EVENTS
#define SCOPED_NAMED_EVENT_TCHAR_CONDITIONAL(Text, Color, bCondition)\
	FWwiseScopedNamedEventConditional ANONYMOUS_VARIABLE(NamedEvent_)(Color, Text, (bCondition));\
	TRACE_CPUPROFILER_EVENT_SCOPE_TEXT_CONDITIONAL(Text, (bCondition));
#else
#define SCOPED_NAMED_EVENT_TCHAR_CONDITIONAL(Text, Color, bCondition)
#endif
#endif

/// Launches a task for asynchronous execution. Equivalent to UE::Tasks::Launch.
/// @param DebugName A unique name for task identification in debugger and profiler, is compiled out in test/shipping builds
/// @param InPriority Task priority that affects when the task will be executed
/// @param InTaskFlags Task config options
/// @param InFunction A functor that will be executed asynchronously
static void LaunchWwiseTask(
	const TCHAR* DebugName,
	EWwiseTaskPriority InPriority,
	EWwiseTaskFlags InTaskFlags,
	TUniqueFunction<void()>&& InFunction)
{
#if UE_5_1_OR_LATER
	if (InPriority == EWwiseTaskPriority::GameThread)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady(
		[DebugName, InFunction = MoveTemp(InFunction)]
		{
			SCOPED_NAMED_EVENT_TCHAR_CONDITIONAL(DebugName, WwiseNamedEvents::Color3, DebugName != nullptr);
			InFunction();
		},
		{}, nullptr, ENamedThreads::GameThread);
	}
	else
	{
		UE::Tasks::Launch(DebugName, MoveTemp(InFunction),
			static_cast<UE::Tasks::ETaskPriority>(InPriority)
#if UE_5_4_OR_LATER
			, UE::Tasks::EExtendedTaskPriority::None, InTaskFlags
#endif
		);
	}
#else
#if !ENABLE_NAMED_EVENTS
	DebugName = nullptr;
#endif
	FFunctionGraphTask::CreateAndDispatchWhenReady([DebugName, InFunction = MoveTemp(InFunction)]
	{
		SCOPED_NAMED_EVENT_TCHAR_CONDITIONAL(DebugName, WwiseNamedEvents::Color3, DebugName != nullptr);
		InFunction();
	},
		{},
		nullptr,
		static_cast<ENamedThreads::Type>(InPriority));
#endif
}

/// Launches a task for asynchronous execution. Equivalent to UE::Tasks::Launch.
/// @param DebugName A unique name for task identification in debugger and profiler, is compiled out in test/shipping builds
/// @param InPriority Task priority that affects when the task will be executed
/// @param InFunction A functor that will be executed asynchronously
static void LaunchWwiseTask(
	const TCHAR* DebugName,
	EWwiseTaskPriority InPriority,
	TUniqueFunction<void()>&& InFunction)
{
#if UE_5_1_OR_LATER
	if (InPriority == EWwiseTaskPriority::GameThread)
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady(
		[DebugName, InFunction = MoveTemp(InFunction)]
		{
			SCOPED_NAMED_EVENT_TCHAR_CONDITIONAL(DebugName, WwiseNamedEvents::Color3, DebugName != nullptr);
			InFunction();
		},
		{}, nullptr, ENamedThreads::GameThread);
	}
	else
	{
		UE::Tasks::Launch(DebugName, MoveTemp(InFunction), static_cast<UE::Tasks::ETaskPriority>(InPriority));
	}
#else
#if !ENABLE_NAMED_EVENTS
	DebugName = nullptr;
#endif
	FFunctionGraphTask::CreateAndDispatchWhenReady([DebugName, InFunction = MoveTemp(InFunction)]
	{
		SCOPED_NAMED_EVENT_TCHAR_CONDITIONAL(DebugName, WwiseNamedEvents::Color3, DebugName != nullptr);
		InFunction();
	},
		{},
		nullptr,
		static_cast<ENamedThreads::Type>(InPriority));
#endif
}

/// Launches a task for asynchronous execution. Equivalent to UE::Tasks::Launch.
/// @param DebugName A unique name for task identification in debugger and profiler, is compiled out in test/shipping builds
/// @param InFunction A functor that will be executed asynchronously
static void LaunchWwiseTask(
	const TCHAR* DebugName,
	TUniqueFunction<void()>&& InFunction)
{
#if UE_5_1_OR_LATER
	UE::Tasks::Launch(DebugName, MoveTemp(InFunction), static_cast<UE::Tasks::ETaskPriority>(EWwiseTaskPriority::Default));
#else
#if !ENABLE_NAMED_EVENTS
	DebugName = nullptr;
#endif
	FFunctionGraphTask::CreateAndDispatchWhenReady([DebugName, InFunction = MoveTemp(InFunction)]
	{
		SCOPED_NAMED_EVENT_TCHAR_CONDITIONAL(DebugName, WwiseNamedEvents::Color1, DebugName != nullptr);
		InFunction();
	},
		{},
		nullptr,
		static_cast<ENamedThreads::Type>(EWwiseTaskPriority::Default));
#endif
}

#if !UE_5_1_OR_LATER
#undef TRACE_CPUPROFILER_EVENT_SCOPE_TEXT_CONDITIONAL
#undef SCOPED_NAMED_EVENT_TCHAR_CONDITIONAL
#endif
