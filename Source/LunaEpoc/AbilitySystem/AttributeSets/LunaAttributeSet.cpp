// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaAttributeSet.h"
#include "Net/UnrealNetwork.h"

ULunaAttributeSet::ULunaAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitStamina(50.f);
	InitMaxStamina(100.f);

}

void ULunaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULunaAttributeSet, Health, OldHealth);
}

void ULunaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULunaAttributeSet, MaxHealth, OldMaxHealth);
}

void ULunaAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULunaAttributeSet, Stamina, OldStamina);
}

void ULunaAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULunaAttributeSet, MaxStamina, OldMaxStamina);
}

void ULunaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ULunaAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ULunaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)

	DOREPLIFETIME_CONDITION_NOTIFY(ULunaAttributeSet, Stamina, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ULunaAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always)
}
