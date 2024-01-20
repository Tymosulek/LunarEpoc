// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LunaEpocCharacter.generated.h"

UCLASS(Blueprintable)
class ALunaEpocCharacter : public ACharacter
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float RotationSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxSprintSpeed = 550.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float InterpolationSpeed = 100.f;


public: /*Functions*/
	ALunaEpocCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void Move(const FVector2D& InputVector);
	void SetSprint(const bool bNewSprint);
	float SpeedModifier() const;


public: /*Properties*/

private: /*functions*/

	void RotateToMouse(float DeltaSeconds);
	void InterpolateSpeed(float TargetSpeed, float DeltaTime);

private: /*properties*/

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	bool bShouldSprint;// = false;
	float CurrentSpeed;// = MaxWalkSpeed;
};

