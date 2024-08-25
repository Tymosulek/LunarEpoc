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

public: /*Properties*/

protected: /*functions*/

	void InterpolateSpeed(float TargetSpeed, float DeltaTime);
	float SpeedModifier() const;

protected: /*properties*/

	float CurrentSpeed = 0;
	float CachedMaxWalkSpeed = 0;

};
