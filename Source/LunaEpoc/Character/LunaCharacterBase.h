// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "LunaEpoc/Weapons/AWeapon.h"
#include "LunaCharacterBase.generated.h"

class ULunaAbilitySystemComponent;
class UAbilitySystemComponent;
class UAttributeSet;
class ULunaCharacterMovementComponent;

UCLASS(Abstract)
class LUNAEPOC_API ALunaCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALunaCharacterBase();
	explicit ALunaCharacterBase(const FObjectInitializer& ObjectInitializer);
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	ULunaCharacterMovementComponent* GetLunaMovementComponent() const;

protected:
	virtual void BeginPlay() override;
	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	// Switch on AbilityID to return individual ability levels. Hardcoded to 1 for every ability in this project.
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual int32 GetAbilityLevel(EGDAbilityInputID AbilityID) const;
	
	// Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	virtual void RemoveCharacterAbilities();

protected:

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon = nullptr;

	UPROPERTY()
	TWeakObjectPtr<ULunaAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class ULunaGameplayAbility>> CharacterAbilities;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	AWeapon* CurrentWeapon{nullptr};
};
