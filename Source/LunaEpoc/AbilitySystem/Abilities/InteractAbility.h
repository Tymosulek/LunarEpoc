// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "LunaGameplayAbility.h"
#include "InteractAbility.generated.h"

class ALunaCharacter;

UCLASS()
class LUNAEPOC_API UInteractAbility : public ULunaGameplayAbility
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Interact")
	float InteractionRadius = 250.f;

public: /*Functions*/

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public: /*Functions*/

	static bool FindInteractableInRange(const ALunaCharacter* Player, TArray<AActor*>& OutInteractables, float Range);
};
