// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "LunaCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class ULunaCharacterMovementComponent;

UCLASS(Abstract)
class LUNAEPOC_API ALunaCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALunaCharacterBase();
	ALunaCharacterBase(const FObjectInitializer& ObjectInitializer);
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	ULunaCharacterMovementComponent* GetLunaMovementComponent() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};
