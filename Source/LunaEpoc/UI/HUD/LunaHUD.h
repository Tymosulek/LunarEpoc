// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LunaHUD.generated.h"

class UInventoryGrid;
class ULunaUserWidget;
class APlayerController;
class APlayerState;
class UAbilitySystemComponent;
class UAttributeSet;
class UOverlayWidgetController;
struct FWidgetControllerParams;

UCLASS()
class LUNAEPOC_API ALunaHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<ULunaUserWidget> OverlayWidget;

	UFUNCTION(BlueprintCallable)
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* As);

	UInventoryGrid* GetInventoryGrid() const {return InventoryWidget;}

	UFUNCTION()
	void ToggleInventoryWidget();

protected: /*functions*/

	void InitInventoryWidget(APlayerController* PC, UOverlayWidgetController* WidgetController);
	void ConfigureInputMode(APlayerController* PlayerController, bool bUIOnly) const;

protected: /*properties*/

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULunaUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UInventoryGrid> InventoryWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UInventoryGrid> InventoryWidget;
};
