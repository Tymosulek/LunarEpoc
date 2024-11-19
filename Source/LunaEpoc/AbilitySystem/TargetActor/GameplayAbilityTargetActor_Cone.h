// Project Luna Epoch
// Craig Palmer

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GameplayAbilityTargetActor_Cone.generated.h"


UCLASS()
class LUNAEPOC_API AGameplayAbilityTargetActor_Cone : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float ConeHalfAngle = 30.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 1000.f;
	
public:
	AGameplayAbilityTargetActor_Cone();
	
	virtual void ConfirmTargetingAndContinue() override;
};
