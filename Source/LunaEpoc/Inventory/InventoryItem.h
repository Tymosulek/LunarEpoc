#pragma once
#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "LunaEpoc/Weapons/AWeapon.h"
#include "InventoryItem.generated.h"

UENUM()
enum class EItemType : uint8
{
	Misc,
	Equipment,
	Consumable,
	Currency
};

UENUM()
enum class EItemQuality : uint8
{
	Poor,
	Common,
	Uncommon,
	Rare,
	Epic,
	Legendary
};

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	EItemQuality Quality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxStackableQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsDroppable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UStaticMesh* WorldMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	USkeletalMesh* EquipmentMesh = nullptr;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	// EEquipmentType EquipmentType;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	// EEquipmentSlot EquipmentSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Armour;
};
