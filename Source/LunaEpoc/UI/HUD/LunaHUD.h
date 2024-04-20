// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LunaHUD.generated.h"

class ULunaUserWidget;

UCLASS()
class LUNAEPOC_API ALunaHUD : public AHUD
{
	GENERATED_BODY()

public:

protected: /*functions*/

	virtual void BeginPlay() override;

protected: /*properties*/

	UPROPERTY(EditAnywhere)
	TSubclassOf<ULunaUserWidget> OverlayWidgetClass;

	
};
