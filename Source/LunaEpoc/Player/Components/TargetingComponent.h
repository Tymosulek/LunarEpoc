// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetingComponent.generated.h"


struct FGameplayAbilityTargetDataHandle;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUNAEPOC_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

public: /*Functions*/
	UTargetingComponent();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void ProcessTargetData(const FGameplayAbilityTargetDataHandle& TargetData, const AActor* AbilityOwner);

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	AActor* GetCurrentTarget() const { return CurrentTarget.Get(); }

protected: /*properties*/

	TWeakObjectPtr<AActor> CurrentTarget = nullptr;
};
