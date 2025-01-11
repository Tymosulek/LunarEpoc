// Project Luna Epoch 


#include "InventoryComponent.h"

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
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UInventoryItem* UInventoryComponent::GetInventoryItem(const int32 Index) const
{
	return Inventory.IsValidIndex(Index) ? Inventory[Index] : nullptr;
}

void UInventoryComponent::SetInventoryItem(const int32 Index, UInventoryItem* InventoryItem)
{
	if (Inventory.IsValidIndex(Index) && InventoryItem)
	{
		Inventory[Index] = InventoryItem;
	}
}

void UInventoryComponent::ClearInventoryItem(const int32 Index)
{
	if (Inventory.IsValidIndex(Index))
	{
		Inventory[Index] = nullptr;
	}
}

int32 UInventoryComponent::GetEmptyInventoryIndex() const
{
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (!Inventory[i]) 
		{
			return i;
		}
	}
	
	return -1;
}

int32 UInventoryComponent::GetInventoryCount() const
{
	int32 Count = 0;
	for (const UInventoryItem* Item : Inventory)
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
		Inventory.Add(nullptr);
	}
}

void UInventoryComponent::DecreaseInventorySize(const int32 Amount)
{
	for (int32 i = 0; i < Amount && Inventory.Num() > 0; i++)
	{
		Inventory.Pop();
	}
}