// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//Game

//Engine
#include "CoreMinimal.h"
#include "Character/LunaCharacterBase.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemInterface.h"

#include "LunaCharacter.generated.h"

UCLASS(Blueprintable)
class ALunaCharacter : public ALunaCharacterBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float RotationSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float InterpolationSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attributes)
	int MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attributes)
	int MaxStamina = 100;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Abilities)
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Abilities)
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;


public: /*Functions*/
	ALunaCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void InitializeAttributes();
	virtual void GiveDefaultAbilities();

	float SpeedModifier() const;

	/** Returns TopDownCameraComponent subject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns our Ability System Component. */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


public: /*Properties*/

protected: /*functions*/

	void RotateToMouse(float DeltaSeconds);
	void InterpolateSpeed(float TargetSpeed, float DeltaTime);

protected: /*properties*/

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class ULunaAttributeSet* Attributes;

	float CurrentSpeed;// = MaxWalkSpeed;
};

