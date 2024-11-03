// Project Luna Epoch 


#include "AWeapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the weapon mesh component
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
}

void AWeapon::Fire()
{
    if (AmmoCount > 0)
    {
        --AmmoCount;
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Weapon Fired!"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Out of Ammo!"));
    }
}

void AWeapon::Reload()
{
    AmmoCount = MaxAmmo;
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Weapon Reloaded!"));
}

