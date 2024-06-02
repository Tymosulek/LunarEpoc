// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LunaHUD.generated.h"

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

protected: /*functions*/


protected: /*properties*/

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULunaUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	
};
