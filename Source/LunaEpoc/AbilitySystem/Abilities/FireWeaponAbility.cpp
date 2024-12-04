// Project Luna Epoch 


#include "FireWeaponAbility.h"
//game
#include "LunaEpoc/LunaCharacter.h"
//engine
#include "AbilitySystemComponent.h"
#include "LunaEpoc/Player/Components/TargetingComponent.h"

UFireWeaponAbility::UFireWeaponAbility()
{
}

bool UFireWeaponAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayTagContainer* SourceTags,
                                            const FGameplayTagContainer* TargetTags,
                                            FGameplayTagContainer* OptionalRelevantTags) const
{
    /* Player must be alive,
     * have a weapon to fire
     * not be in cooldown .
     * Regardless of ammo remaining.*/
    
    const ALunaCharacter* LunaCharacter = Cast<ALunaCharacter>(GetAvatarActorFromActorInfo());
    if (!LunaCharacter || !LunaCharacter->IsAlive())
    {
        return false;
    }

    const AWeapon* Weapon = LunaCharacter->GetWeapon();
    if (!Weapon || Weapon->IsInCooldown())
    {
        return false;
    }

    return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UFireWeaponAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    
    FireWeaponLogic();
    
    K2_EndAbility();
}

void UFireWeaponAbility::FireWeaponLogic() const
{
    const ALunaCharacter* LunaCharacter = Cast<ALunaCharacter>(GetAvatarActorFromActorInfo());
    if (!LunaCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("FireWeaponLogic: Invalid character!"));
        return;
    }

    // Get placeholder weapon from character.
    AWeapon* Weapon = LunaCharacter->GetWeapon();
    if (!Weapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("FireWeaponLogic: Weapon not found!"));
        return;
    }

    // Reduce ammo count
    if (Weapon->AmmoCount <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("FireWeaponLogic: Out of ammo!"));
        return;
    }
    
    Weapon->AmmoCount--;

    // Get start and end locations for the line trace
    FVector Start = Weapon->GetActorLocation();
    FVector ForwardVector = Weapon->GetActorForwardVector();
    FVector End = Start + (ForwardVector * 1000.0f);

    //Update end point to be current target if valid.
    UTargetingComponent* TargetingComponent = LunaCharacter->GetTargetingComponent();
    if (TargetingComponent && TargetingComponent->GetCurrentTarget())
    {
        End = TargetingComponent->GetCurrentTarget()->GetActorLocation();
    }
    
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(LunaCharacter); // Ignore the character during the trace
    QueryParams.AddIgnoredActor(Weapon);        // Ignore the weapon itself

    // Perform the line trace
    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, QueryParams))
    {
        if (AActor* HitActor = HitResult.GetActor())
        {
            UE_LOG(LogTemp, Log, TEXT("FireWeaponLogic: Hit Actor: %s"), *HitActor->GetName());
        }

        // Update end so accurate represents impact point in gameplay cue.
        End = HitResult.ImpactPoint;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("FireWeaponLogic: No hit detected."));
    }

    // Draw debug line - placeholder until vfx in place.
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 2.0f);

    // Trigger gameplay cue for impact
    FGameplayCueParameters CueParams;
    CueParams.Location = End;
    CueParams.Normal = -ForwardVector;
    CueParams.EffectCauser = const_cast<ALunaCharacter*>(LunaCharacter);
    CueParams.PhysicalMaterial = HitResult.PhysMaterial;

    // Trigger the gameplay cue
    if (UAbilitySystemComponent* Asc = LunaCharacter->GetAbilitySystemComponent())
    {
        Asc->ExecuteGameplayCue(
            FGameplayTag::RequestGameplayTag(FName("GameplayCue.FireWeapon.Impact")),
            CueParams
        );
    }

    // Tell weapon we've fired it so can cool down.
    Weapon->OnFire();
}