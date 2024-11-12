// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LunaCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class LUNAEPOC_API ULunaCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Luna)
	float InterpolationSpeed = 100.f;

public: /*Functions*/

	ULunaCharacterMovementComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Aim Down Sights
	UFUNCTION(BlueprintCallable, Category = "Aim Down Sights")
	void StartAimDownSights();
	UFUNCTION(BlueprintCallable, Category = "Aim Down Sights")
	void StopAimDownSights();
	
public: /*Properties*/

	uint8 bRequestToStartAds : 1;

protected: /*functions*/

	void InterpolateSpeed(float TargetSpeed, float DeltaTime);
	float SpeedModifier() const;

protected: /*properties*/

	float CurrentSpeed = 0;
	float CachedMaxWalkSpeed = 0;

};
