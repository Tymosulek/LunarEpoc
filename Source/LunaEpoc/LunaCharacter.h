// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//Game
#include "Character/LunaCharacterBase.h"

//Engine
#include "CoreMinimal.h"

#include "LunaCharacter.generated.h"

class UInventoryComponent;

UCLASS(Blueprintable)
class ALunaCharacter : public ALunaCharacterBase
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float RotationSpeed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attributes)
	int MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attributes)
	int MaxStamina = 100;
	
	// This is extremely temporary, will replace with a proper socket and applied to player via an inventory component at some point.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* Temp_Weapon;

public: /*Functions*/
	ALunaCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UTargetingComponent* GetTargetingComponent() const { return TargetingComponent; }

	// Called from both SetupPlayerInputComponent and OnRep_PlayerState because of a potential race condition where the PlayerController might
	// call ClientRestart which calls SetupPlayerInputComponent before the PlayerState is replicated to the client so the PlayerState would be null in SetupPlayerInputComponent.
	// Conversely, the PlayerState might be replicated before the PlayerController calls ClientRestart so the Actor's InputComponent would be null in OnRep_PlayerState.
	void BindASCInput();

	// This is extremely temporary, will replace with a nice inventory component at some point
	AWeapon* GetWeapon() const;

	bool IsAlive() const;

public: /*Properties*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	class USphereComponent* InteractionCollider;

public: /*Functions*/

	void InitAbilityActorInfo();
	void RotateToMouse(float DeltaSeconds);

protected: /*properties*/

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom = nullptr;
	
	//Used during combat to find the current target.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Targeting")
	TObjectPtr<UTargetingComponent> TargetingComponent = nullptr;

	UPROPERTY()
	TObjectPtr<class UAIPerceptionStimuliSourceComponent> StimuliSource = nullptr;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent = nullptr;
	
	bool ASCInputBound = false;
};

