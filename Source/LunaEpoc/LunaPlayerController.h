// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "Templates/SubclassOf.h"
#include "LunaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ALunaPlayerController : public APlayerController
{
	GENERATED_BODY()

public: /*Designer Facing*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext{nullptr};
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InventoryAction{nullptr};

public: /*Functions*/
	ALunaPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected: /*functions*/
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	void Move(const FInputActionValue& Value);
	void CursorTrace();

protected: /*properties*/

	IEnemyInterface* LastActor = nullptr;
	IEnemyInterface* ThisActor = nullptr;
};


