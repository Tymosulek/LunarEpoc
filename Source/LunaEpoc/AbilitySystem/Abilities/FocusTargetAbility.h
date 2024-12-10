// Project Luna Epoch
// Craig Palmer

#pragma once

#include "CoreMinimal.h"
#include "LunaGameplayAbility.h"
#include "FocusTargetAbility.generated.h"

class AGameplayAbilityTargetActor_Cone;
class AGameplayAbilityTargetActor;
/**
 * Focus - RMB - HOLD: Holding down the RMB input focuses the players sight & vision cone onto the target, increasing accuracy.
 * Targeting Angle: Within the Vision Cone there will be a targeting angle that detects enemies.
 * Enemies that have been within the targeting angle for a [tunable] amount of seconds, will be automatically targeted.
 */
UCLASS()
class LUNAEPOC_API UFocusTargetAbility : public ULunaGameplayAbility
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Luna)
	float TargetingAngle = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Luna)
	float TargetingRange = 1000.f;

public: /*Functions*/
	UFocusTargetAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

protected: /*functions*/

	UFUNCTION()
	void ProcessTargetData(const FGameplayAbilityTargetDataHandle& TargetData);

	UFUNCTION()
	void UpdateClosestTarget();

protected: /*properties*/

	FTimerHandle TargetUpdateTimerHandle; 
	
	UPROPERTY()
	TObjectPtr<AGameplayAbilityTargetActor_Cone> TargetActor = nullptr;

};