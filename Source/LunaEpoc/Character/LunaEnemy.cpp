// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaEnemy.h"
#include "LunaEpoc/LunaEpoc.h"
#include "LunaEpoc/AbilitySystem/Components/LunaAbilitySystemComponent.h"
#include "LunaEpoc/AbilitySystem/AttributeSets/LunaAttributeSet.h"

ALunaEnemy::ALunaEnemy()
{
	if (USkeletalMeshComponent* CharacterMesh = GetMesh())
	{
		CharacterMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	}

	//Setup ASC
	AbilitySystemComponent = CreateDefaultSubobject<ULunaAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//Set replication mode to Minimal as will be an AI controlled character.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);


	//Setup Attributes
	AttributeSet = CreateDefaultSubobject<ULunaAttributeSet>(TEXT("AttributeSet"));
}

void ALunaEnemy::HighlightActor()
{
	if (USkeletalMeshComponent* CharacterMesh = GetMesh())
	{
		CharacterMesh->SetRenderCustomDepth(true);
		CharacterMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void ALunaEnemy::UnHighlightActor()
{
	if (USkeletalMeshComponent* CharacterMesh = GetMesh())
	{
		CharacterMesh->SetRenderCustomDepth(false);
	}
	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(false);
	}
}

void ALunaEnemy::BeginPlay()
{
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
