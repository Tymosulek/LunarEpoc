// Project Luna Epoch 


#include "AWeapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the weapon mesh component
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::PlayFireAnimation()
{
    // Logic for playing the firing animation
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Fire()
{
    if (AmmoCount > 0)
    {
        --AmmoCount;
        PlayFireAnimation();
        // Logic to deal damage to target here
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

