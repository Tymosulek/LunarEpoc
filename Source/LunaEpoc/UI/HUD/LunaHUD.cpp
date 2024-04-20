// Project Luna Epoch 


#include "LunaHUD.h"
#include "../Widget/LunaUserWidget.h"
#include "Subsystems/PanelExtensionSubsystem.h"


void ALunaHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
