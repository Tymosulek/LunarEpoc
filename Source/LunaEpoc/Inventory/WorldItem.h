#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "WorldItem.generated.h"

class UInventoryItem;

UCLASS()
class LUNAEPOC_API AWorldItem : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UInventoryItem* InventoryItem = nullptr;

protected:
	AWorldItem();
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor) override;

	UFUNCTION(BlueprintCallable, Category = Item)
	UInventoryItem* GetInventoryItem() const;

};
