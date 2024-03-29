// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaEnemy.h"
#include "LunaEpoc/LunaEpoc.h"

ALunaEnemy::ALunaEnemy()
{
	if (USkeletalMeshComponent* CharacterMesh = GetMesh())
	{
		CharacterMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	}
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
