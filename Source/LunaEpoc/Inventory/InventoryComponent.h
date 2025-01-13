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
	virtual ~UInventoryComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UInventoryItem* GetInventoryItem(int32 Index) const;
	void SetInventoryItem(int32 Index, UInventoryItem* InventoryItem);
	void ClearInventoryItem(int32 Index);
	int32 GetEmptyInventoryIndex() const;
	int32 GetInventoryCount() const;
	void IncreaseInventorySize(int32 Amount);
	void DecreaseInventorySize(int32 Amount);
	
	TArray<UInventoryItem*> GetInventoryItems() const {return Inventory;}

public: /*Properties*/

protected: /*functions*/
	virtual void BeginPlay() override;

protected: /*properties*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<UInventoryItem*> Inventory;
};
