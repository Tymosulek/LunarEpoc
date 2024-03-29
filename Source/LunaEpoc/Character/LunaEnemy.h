// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LunaCharacterBase.h"
#include "LunaEpoc/Interaction/EnemyInterface.h"
#include "LunaEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LUNAEPOC_API ALunaEnemy : public ALunaCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public: /*Designer Facing*/

public: /*Functions*/
	ALunaEnemy();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected: /*functions*/

protected: /*properties*/

};
