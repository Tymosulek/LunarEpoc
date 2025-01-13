// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "LunaGameplayAbility.h"
#include "MeleeAttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class LUNAEPOC_API UMeleeAttackAbility : public ULunaGameplayAbility
{
	GENERATED_BODY()


	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	bool ShouldApplyDamageToActor(AActor* Actor) const;

	void ApplyDamageToActor(AActor* HitActor, const FGameplayAbilityActorInfo* ActorInfo);

public:
	// The range of the melee attack
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeRange{200.0f};

	// The radius of the melee attack's hit detection
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeRadius = {100.0f};

	// Gameplay effect to apply as damage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	TSubclassOf<class UGameplayEffect> DamageEffectClass;

	// The level of the damage effect to apply
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float DamageEffectLevel {1.0f};

	// Object types to consider when performing hit detection
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
};
