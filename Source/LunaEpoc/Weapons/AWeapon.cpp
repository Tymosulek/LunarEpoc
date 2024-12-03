// Project Luna Epoch 


#include "AWeapon.h"

static TAutoConsoleVariable<int32> CVarEnableWeaponDebug(
    TEXT("Weapon.EnableDebug"),
    0,
    TEXT("Enable or disable weapon-specific debug messages. 1 = Enable, 0 = Disable."),
    ECVF_Default);

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeapon::OnFire()
{
    // Timer should not have been set.
    check(!CooldownTimerHandle.IsValid());

    LogDebugMessage(TEXT("Weapon begin cooldown"));
    
    GetWorld()->GetTimerManager().SetTimer(
        CooldownTimerHandle,
        [this]()
        {
            CooldownTimerHandle.Invalidate();
            LogDebugMessage(TEXT("Weapon end cooldown"));
        },
        RateOfFire,
        false
    );
}

void AWeapon::Reload()
{
    AmmoCount = MaxAmmo;
    LogDebugMessage(TEXT("Weapon Reloaded!"));
}

bool AWeapon::IsInCooldown() const
{
    return CooldownTimerHandle.IsValid();
}

void AWeapon::LogDebugMessage(const FString& Message)
{
    if (CVarEnableWeaponDebug->GetInt() == 1 && GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, Message);
    }
}