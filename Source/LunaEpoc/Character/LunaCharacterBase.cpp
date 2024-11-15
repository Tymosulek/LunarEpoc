// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "LunaCharacterMovementComponent.h"
#include "LunaEpoc/AbilitySystem/Abilities/LunaGameplayAbility.h"
#include "LunaEpoc/AbilitySystem/Components/LunaAbilitySystemComponent.h"


ALunaCharacterBase::ALunaCharacterBase()
{
}

ALunaCharacterBase::ALunaCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<ULunaCharacterMovementComponent>(
		ACharacter::CharacterMovementComponentName))

{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ALunaCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
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
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale,
			                                 TEXT("WeaponSocket"));
		}
	}
}

void ALunaCharacterBase::AddCharacterAbilities()
{
	// Check if the function is running on the server
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	// Check if AbilitySystemComponent is valid
	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	// Check if character abilities have already been given
	if (AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}
	for (TSubclassOf<ULunaGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID),
			                     static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = true;
}

int32 ALunaCharacterBase::GetAbilityLevel(EGDAbilityInputID AbilityID) const
{
	return 1;
}

void ALunaCharacterBase::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}

	// Remove any abilities added from a previous call. This checks to make sure the ability is in the startup 'CharacterAbilities' array.
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	// Do in two passes so the removal happens after we have the full list
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = false;
}
