// Project Luna Epoch 


#include "LunaHUD.h"

#include "../Widget/LunaUserWidget.h"
#include "../WidgetController/OverlayWidgetController.h"
#include "Subsystems/PanelExtensionSubsystem.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"


UOverlayWidgetController* ALunaHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependancies();
	}

	return OverlayWidgetController;
}

void ALunaHUD::InitOverlay(APlayerController* Pc, APlayerState* Ps, UAbilitySystemComponent* Asc, UAttributeSet* As)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class unitialized, please fill out BP_AuraHUD"));

	if (UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass))
	{
		//cache overlay widget to HUD
		OverlayWidget = Cast<ULunaUserWidget>(Widget);

		//create widget controller for overlay widget
		const FWidgetControllerParams Params(Pc, Ps, Asc, As);
		UOverlayWidgetController* WidgetController = GetOverlayWidgetController(Params);

		OverlayWidget->SetWidgetController(WidgetController);

		WidgetController->BroadcastInitialValues();

		//add to player screen.
		OverlayWidget->AddToViewport();
	}
}