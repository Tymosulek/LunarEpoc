// Project Luna Epoch 


#include "TargetingComponent.h"

#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

static TAutoConsoleVariable<int32> CVarEnableTargetingDebug(
	TEXT("Targeting.EnableDebug"),
	0,
	TEXT("Enable or disable targeting-specific debug messages. 1 = Enable, 0 = Disable."),
	ECVF_Default);

UTargetingComponent::UTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTargetingComponent::ProcessTargetData(const FGameplayAbilityTargetDataHandle& TargetData,
                                            const AActor* AbilityOwner)
{
	if (!TargetData.IsValid(0))
	{
		CurrentTarget = nullptr;
		return;
	}

	AActor* ClosestTarget = nullptr;
	float ClosestDistanceSquared = MAX_FLT;

	for (const TSharedPtr<FGameplayAbilityTargetData>& Data : TargetData.Data)
	{
		if (!Data.IsValid())
		{
			continue;
		}

		for (TWeakObjectPtr<AActor> DataTargetActor : Data->GetActors())
		{
			if (DataTargetActor.IsValid())
			{
				const float DistanceSquared = FVector::DistSquared(DataTargetActor->GetActorLocation(),
				                                                   AbilityOwner->GetActorLocation());
				if (DistanceSquared < ClosestDistanceSquared)
				{
					ClosestTarget = DataTargetActor.Get();
					ClosestDistanceSquared = DistanceSquared;
				}
			}
		}
	}

	const bool bNewTarget = CurrentTarget != ClosestTarget;
	CurrentTarget = ClosestTarget;

	if (CurrentTarget.Get())
	{
		if (UAbilitySystemComponent* Asc = AbilityOwner->FindComponentByClass<UAbilitySystemComponent>())
		{
			Asc->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(TEXT("State.Targeting.Focused")));
		}

		//Debug helper.
		if (CVarEnableTargetingDebug->GetInt() == 1 && GEngine)
		{
			if (bNewTarget)
			{
				UE_LOG(LogTemp, Log, TEXT("Current target updated to: %s"), *CurrentTarget->GetName());
			}

			DrawDebugSphere(GetWorld(), CurrentTarget->GetActorLocation(), 50.f, 12, FColor::Green, false, 1.f);
		}
	}
	else
	{
		if (UAbilitySystemComponent* Asc = AbilityOwner->FindComponentByClass<UAbilitySystemComponent>())
		{
			Asc->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(TEXT("State.Targeting.Focused")));
		}

		//Debug helper.
		if (CVarEnableTargetingDebug->GetInt() == 1 && GEngine)
		{
			UE_LOG(LogTemp, Log, TEXT("Current target cleared."));
		}
	}
}
