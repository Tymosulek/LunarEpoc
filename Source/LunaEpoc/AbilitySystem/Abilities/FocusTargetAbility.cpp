// Project Luna Epoch
// Craig Palmer


#include "FocusTargetAbility.h"

#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "LunaEpoc/AbilitySystem/TargetActor/GameplayAbilityTargetActor_Cone.h"
#include "LunaEpoc/Player/Components/TargetingComponent.h"

UFocusTargetAbility::UFocusTargetAbility()
{
}

void UFocusTargetAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//Should always be valid to have activated ability in first place, but handy way to get ASC.
	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	//CP - Set up the targeting actor
	TargetActor = GetWorld()->SpawnActor<AGameplayAbilityTargetActor_Cone>();
	if (!TargetActor)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	FGameplayAbilityTargetingLocationInfo StartLocationInfo;
	StartLocationInfo.LocationType = EGameplayAbilityTargetingLocationType::ActorTransform;
	StartLocationInfo.SourceActor = ActorInfo->AvatarActor.Get();

	TargetActor->StartLocation = StartLocationInfo;
	TargetActor->TargetingRange = TargetingRange;
	TargetActor->ConeHalfAngle = TargetingAngle;
	TargetActor->ShouldProduceTargetDataOnServer = true;

	TargetActor->TargetDataReadyDelegate.AddUObject(this, &UFocusTargetAbility::ProcessTargetData);

	//CP - periodically call ConfirmTargetingAndContinue to update target data.
	GetWorld()->GetTimerManager().SetTimer(TargetUpdateTimerHandle, this, &UFocusTargetAbility::UpdateClosestTarget,
	                                       0.1f, true);

	//CP - Ability to remain active until input released.
	bIsActive = true;
}

void UFocusTargetAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	//CP - Cleanup timer as will remain active otherwise.
	GetWorld()->GetTimerManager().ClearTimer(TargetUpdateTimerHandle);
	TargetUpdateTimerHandle.Invalidate();
	
	if (TargetActor)
	{
		TargetActor->Destroy();
		TargetActor = nullptr;
	}
}

void UFocusTargetAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	//CP - Ability ends when RMB is released.
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

// ReSharper disable once CppMemberFunctionMayBeConst 
void UFocusTargetAbility::UpdateClosestTarget()
{
	if (!TargetActor || !TargetActor->ShouldProduceTargetDataOnServer)
	{
		return;
	}

	//CP - When called will return new up-to-date target data from cone actor.
	TargetActor->ConfirmTargetingAndContinue();
}

void UFocusTargetAbility::ProcessTargetData(const FGameplayAbilityTargetDataHandle& TargetData)
{
	const AActor* AbilityOwner = GetAvatarActorFromActorInfo();
	check(AbilityOwner);

	if (UTargetingComponent* TargetingComponent = AbilityOwner->FindComponentByClass<UTargetingComponent>())
	{
		TargetingComponent->ProcessTargetData(TargetData, AbilityOwner);
	}
}