// Project Luna Epoch 


#include "AWeapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeapon::OnFire()
{
    // Timer should not have been set.
    check(!CooldownTimerHandle.IsValid());

    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Weapon begin cooldown"));

    GetWorld()->GetTimerManager().SetTimer(
        CooldownTimerHandle,
        [this]()
        {
            CooldownTimerHandle.Invalidate();
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Weapon end cooldown"));
        },
        RateOfFire,
        false
    );
}

void AWeapon::Reload()
{
    AmmoCount = MaxAmmo;
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Weapon Reloaded!"));
}

bool AWeapon::IsInCooldown() const
{
    return CooldownTimerHandle.IsValid();
}

