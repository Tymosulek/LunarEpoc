// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNAEPOC_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

public: /*Functions*/	
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: /*Properties*/

protected: /*functions*/
	virtual void BeginPlay() override;

protected: /*properties*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItem> Inventory;
};
