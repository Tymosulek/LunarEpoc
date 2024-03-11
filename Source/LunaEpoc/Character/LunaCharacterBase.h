// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LunaCharacterBase.generated.h"

UCLASS(Abstract)
class LUNAEPOC_API ALunaCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ALunaCharacterBase();

protected:
	virtual void BeginPlay() override;

};
