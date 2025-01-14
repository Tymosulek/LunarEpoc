#include "WorldItem.h"

#include "InventoryComponent.h"
#include "LunaEpoc/LunaCharacter.h"

AWorldItem::AWorldItem()
{
	PrimaryActorTick.bCanEverTick = true;

	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void AWorldItem::BeginPlay()
{
	Super::BeginPlay();
}

void AWorldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldItem::Interact(AActor* Interactor)
{
	if (const ALunaCharacter* Character = Cast<ALunaCharacter>(Interactor))
	{
		if (UInventoryComponent* Inventory = Character->FindComponentByClass<UInventoryComponent>())
		{
			const int32 AvailableIndex = Inventory->GetEmptyInventoryIndex();
			if (AvailableIndex >= 0)
			{
				Inventory->SetInventoryItem(AvailableIndex, InventoryItem);

				//This actor doesnt need to exist anymore
				Destroy();
			}
		}
	}
}

UInventoryItem* AWorldItem::GetInventoryItem() const
{
	return InventoryItem;
}
