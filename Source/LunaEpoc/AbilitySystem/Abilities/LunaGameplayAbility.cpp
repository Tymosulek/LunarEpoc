// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaGameplayAbility.h"

#include "AbilitySystemComponent.h"

ULunaGameplayAbility::ULunaGameplayAbility()
{
	// Default to Instance Per Actor
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void ULunaGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
