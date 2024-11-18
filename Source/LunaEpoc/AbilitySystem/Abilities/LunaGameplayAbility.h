// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LunaEpoc/LunaEpoc.h"
#include "LunaGameplayAbility.generated.h"

/**
 * Common behaviour between all Luna Gameplay Abilities.
 */
UCLASS()
class LUNAEPOC_API ULunaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EGDAbilityInputID AbilityInputID = EGDAbilityInputID::None;

	// Value to associate an ability with a slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EGDAbilityInputID AbilityID = EGDAbilityInputID::None;

	// Tells an ability to activate immediately when it's granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	//Apply this gameplay effect if valid while ability active and remove when ability ends.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	TSubclassOf<UGameplayEffect> EffectClass;

public: /*Functions*/
	
	ULunaGameplayAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected: /*functions*/
protected: /*properties*/

	FActiveGameplayEffectHandle AppliedEffectHandle;
};
