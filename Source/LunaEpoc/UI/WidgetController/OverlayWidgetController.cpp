// Project Luna Epoch 


#include "OverlayWidgetController.h"
#include "LunaEpoc/AbilitySystem/AttributeSets/LunaAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	if (const ULunaAttributeSet* LunaAttributeSet = CastChecked<ULunaAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(LunaAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(LunaAttributeSet->GetMaxHealth());

		OnStaminaChanged.Broadcast(LunaAttributeSet->GetStamina());
		OnMaxStaminaChanged.Broadcast(LunaAttributeSet->GetMaxStamina());
	}
}

void UOverlayWidgetController::BindCallbacksToDependancies()
{
	if (const ULunaAttributeSet* LunaAttributeSet = CastChecked<ULunaAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			LunaAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			LunaAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::MaxHealthChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			LunaAttributeSet->GetStaminaAttribute()).AddUObject(this, &ThisClass::StaminaChanged);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			LunaAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &ThisClass::MaxStaminaChanged);
	}
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::StaminaChanged(const FOnAttributeChangeData& Data)
{
	OnStaminaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}
