// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "LunaEpoc/UI/Widget/LunaUserWidget.h"
#include "InventoryGrid.generated.h"


class UInventoryComponent;

UCLASS()
class LUNAEPOC_API UInventoryGrid : public ULunaUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void SetItemNameAndDescription(const FText& NewName, const FText& NewDescription);

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void RefreshInventory(UInventoryComponent* InventoryComponent);
};
