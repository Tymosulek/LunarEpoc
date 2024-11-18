// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaGameplayAbility.h"

#include "AbilitySystemComponent.h"

ULunaGameplayAbility::ULunaGameplayAbility()
{
	// Default to Instance Per Actor
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULunaGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (IsValid(EffectClass))
	{
		//Sometimes, will wish to apply a gameplay effect when the ability activates.
		if (UAbilitySystemComponent* Asc = ActorInfo->AbilitySystemComponent.Get())
		{
			AppliedEffectHandle = Asc->ApplyGameplayEffectToSelf(
				EffectClass.GetDefaultObject(), 1, Asc->MakeEffectContext());
		}
	}
}

void ULunaGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	//Check if gameplay effect was applied, and remove if required.
	if (AppliedEffectHandle.IsValid() && ActorInfo->AbilitySystemComponent.Get())
	{
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(AppliedEffectHandle);
	}
}

void ULunaGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
