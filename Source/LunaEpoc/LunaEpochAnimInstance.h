// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LunaEpochAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LUNAEPOC_API ULunaEpochAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    // Constructor
    ULunaEpochAnimInstance();

    // Function to update animation (override from UAnimInstance)
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;


protected:

    UPROPERTY(BlueprintReadOnly)
    float Speed;

    UPROPERTY(BlueprintReadOnly)
    float DirectionDegrees;

};
