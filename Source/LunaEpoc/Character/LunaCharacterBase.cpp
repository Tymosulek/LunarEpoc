// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaCharacterBase.h"
#include "LunaCharacterMovementComponent.h"


ALunaCharacterBase::ALunaCharacterBase()
{
}

ALunaCharacterBase::ALunaCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<ULunaCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))

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

ULunaCharacterMovementComponent* ALunaCharacterBase::GetLunaMovementComponent() const
{
	return GetCharacterMovement<ULunaCharacterMovementComponent>();
}

void ALunaCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(DefaultWeaponClass))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass, SpawnParams);
		if (CurrentWeapon)
		{
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket"));
		}
	}
	
}
