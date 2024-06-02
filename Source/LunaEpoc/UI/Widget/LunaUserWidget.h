// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LunaUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LUNAEPOC_API ULunaUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject>  WidgetController;

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* NewController);
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};