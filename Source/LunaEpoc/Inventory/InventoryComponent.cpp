// Project Luna Epoch 


#include "InventoryComponent.h"

#include "LunaEpoc/UI/HUD/LunaHUD.h"
#include "LunaEpoc/UI/Inventory/InventoryGrid.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UInventoryComponent::~UInventoryComponent()
{
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InventoryItems.SetNum(InventorySize);

	if (UInventoryGrid* InventoryGrid = GetInventoryGrid())
	{
		InventoryGrid->RefreshInventory(this);
	}
}

UInventoryGrid* UInventoryComponent::GetInventoryGrid() const
{
	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return nullptr;
	}
	
	const ALunaHUD* HUD = OwnerPawn->GetController<APlayerController>() 
							  ? OwnerPawn->GetController<APlayerController>()->GetHUD<ALunaHUD>() 
							  : nullptr;

	if (!HUD)
	{
		return nullptr;
	}
	
	return HUD->GetInventoryGrid();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UInventoryItem* UInventoryComponent::GetInventoryItem(const int32 Index) const
{
	return InventoryItems.IsValidIndex(Index) ? InventoryItems[Index] : nullptr;
}

void UInventoryComponent::SetInventoryItem(const int32 Index, UInventoryItem* InventoryItem)
{
	if (InventoryItems.IsValidIndex(Index) && InventoryItem)
	{
		InventoryItems[Index] = InventoryItem;
	}
}

void UInventoryComponent::ClearInventoryItem(const int32 Index)
{
	if (InventoryItems.IsValidIndex(Index))
	{
		InventoryItems[Index] = nullptr;
	}
}

int32 UInventoryComponent::GetEmptyInventoryIndex() const
{
	for (int32 i = 0; i < InventoryItems.Num(); i++)
	{
		if (!InventoryItems[i]) 
		{
			return i;
		}
	}
	
	return -1;
}

int32 UInventoryComponent::GetInventoryCount() const
{
	int32 Count = 0;
	for (const UInventoryItem* Item : InventoryItems)
	{
		if (Item)
		{
			Count++;
		}
	}
	return Count;
}

void UInventoryComponent::IncreaseInventorySize(const int32 Amount)
{
	for (int32 i = 0; i < Amount; i++)
	{
		InventoryItems.Add(nullptr);
	}
}

void UInventoryComponent::DecreaseInventorySize(const int32 Amount)
{
	for (int32 i = 0; i < Amount && InventoryItems.Num() > 0; i++)
	{
		InventoryItems.Pop();
	}
}