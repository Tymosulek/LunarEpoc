// Project Luna Epoch 


#include "LunaHUD.h"

//engine
#include "GameFramework/PlayerController.h"\
//game
#include "LunaEpoc/UI/Inventory/InventoryGrid.h"
#include "LunaEpoc/UI/Widget/LunaUserWidget.h"
#include "LunaEpoc/UI/WidgetController/OverlayWidgetController.h"


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

void ALunaHUD::InitInventoryWidget(APlayerController* PC, UOverlayWidgetController* WidgetController)
{
	if (!InventoryWidgetClass) 
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryWidgetClass is uninitialized. Please set it in the Blueprint."));
		return;
	}

	if (!InventoryWidget && GetWorld()) 
	{
		InventoryWidget = CreateWidget<UInventoryGrid>(GetWorld(), InventoryWidgetClass);

		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
			InventoryWidget->SetWidgetController(WidgetController);
		}
	}
}

void ALunaHUD::ConfigureInputMode(APlayerController* PlayerController, const bool bUIOnly) const
{
	if (!PlayerController)
		return;

	PlayerController->SetShowMouseCursor(bUIOnly);

	if (bUIOnly)
	{
		// Set input mode to UI only and focus the inventory widget
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
	}
	else
	{
		// Revert to game-only input mode
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ALunaHUD::ToggleInventoryWidget()
{
	// Validate InventoryWidget and PlayerController
	if (!InventoryWidget || !GetOwningPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("ToggleInventoryWidget failed: InventoryWidget or PlayerController is null."));
		return;
	}

	APlayerController* PlayerController = GetOwningPlayerController();

	if (!InventoryWidget->IsInViewport())
	{
		// Show the widget and configure input for UI
		InventoryWidget->AddToViewport();
		ConfigureInputMode(PlayerController, true);
		UE_LOG(LogTemp, Log, TEXT("Inventory widget displayed."));
	}
	else
	{
		// Hide the widget and restore gameplay input
		InventoryWidget->RemoveFromParent();
		ConfigureInputMode(PlayerController, false);
		UE_LOG(LogTemp, Log, TEXT("Inventory widget hidden."));
	}
}
