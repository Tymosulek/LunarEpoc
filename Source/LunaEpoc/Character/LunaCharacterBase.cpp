// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaCharacterBase.h"

ALunaCharacterBase::ALunaCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

UAbilitySystemComponent* ALunaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ALunaCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ALunaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
