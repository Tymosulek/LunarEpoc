// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaEpocAttributeSet.h"
#include "Net/UnrealNetwork.h"

ULunaEpocAttributeSet::ULunaEpocAttributeSet()
{

}

void ULunaEpocAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION_NOTIFY(ULunaEpocAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ULunaEpocAttributeSet, Stamina, COND_None, REPNOTIFY_Always)
}

void ULunaEpocAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULunaEpocAttributeSet, Health, OldHealth);
}

void ULunaEpocAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULunaEpocAttributeSet, Stamina, OldStamina);
}
