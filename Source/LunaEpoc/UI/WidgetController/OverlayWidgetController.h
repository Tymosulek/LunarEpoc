// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "LunaWidgetController.h"
#include "Delegates/DelegateCombinations.h"

#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChangedSignature, float, NewStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxStaminaChangedSignature, float, NewMaxStamina);

UCLASS(BlueprintType, Blueprintable)
class LUNAEPOC_API UOverlayWidgetController : public ULunaWidgetController
{
	GENERATED_BODY()

	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependancies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnStaminaChangedSignature OnStaminaChanged;

	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxStaminaChangedSignature OnMaxStaminaChanged;

protected:

	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);

	void StaminaChanged(const FOnAttributeChangeData& Data);
	void MaxStaminaChanged(const FOnAttributeChangeData& Data);
	
};
