// Project Luna Epoch 


#include "LunaWidgetController.h"
#include "AbilitySystemComponent.h"

void ULunaWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void ULunaWidgetController::BroadcastInitialValues()
{
}

void ULunaWidgetController::BindCallbacksToDependancies()
{
}
