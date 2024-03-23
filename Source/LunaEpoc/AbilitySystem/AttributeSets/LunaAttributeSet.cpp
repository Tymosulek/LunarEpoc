// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaAttributeSet.h"
#include "Net/UnrealNetwork.h"

ULunaAttributeSet::ULunaAttributeSet()
{
}

void ULunaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(ULunaAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ULunaAttributeSet, Stamina, COND_None, REPNOTIFY_Always)
}

void ULunaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULunaAttributeSet, Health, OldHealth);
}

void ULunaAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULunaAttributeSet, Stamina, OldStamina);
}
