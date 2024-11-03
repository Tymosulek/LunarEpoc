// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//Game
#include "Character/LunaCharacterBase.h"

//Engine
#include "CoreMinimal.h"

#include "LunaCharacter.generated.h"

UCLASS(Blueprintable)
class ALunaCharacter : public ALunaCharacterBase
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float RotationSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attributes)
	int MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attributes)
	int MaxStamina = 100;


public: /*Functions*/
	ALunaCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


public: /*Properties*/

protected: /*functions*/

	void InitAbilityActorInfo();
	void RotateToMouse(float DeltaSeconds);


protected: /*properties*/

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
};

