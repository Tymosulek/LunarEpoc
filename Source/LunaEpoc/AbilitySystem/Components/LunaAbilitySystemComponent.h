// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "LunaAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class LUNAEPOC_API ULunaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool bCharacterAbilitiesGiven = false;
	
};
