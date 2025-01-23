// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "LunaEpoc/UI/Widget/LunaUserWidget.h"
#include "ItemSlot.generated.h"


UCLASS()
class LUNAEPOC_API UItemSlot : public ULunaUserWidget
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

public: /*Functions*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshSlot();

public: /*Properties*/

protected: /*functions*/

protected: /*properties*/
	
};
