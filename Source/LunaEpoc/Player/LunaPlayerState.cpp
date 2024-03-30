// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaPlayerState.h"
#include "LunaEpoc/AbilitySystem/AttributeSets/LunaAttributeSet.h"
#include "LunaEpoc/AbilitySystem/Components/LunaAbilitySystemComponent.h"

ALunaPlayerState::ALunaPlayerState()
{
	//Setup ASC
	AbilitySystemComponent = CreateDefaultSubobject<ULunaAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	//Set replication mode to Mixed as is player controlled.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	//Setup Attributes
	AttributeSet = CreateDefaultSubobject<ULunaAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ALunaPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ALunaPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
