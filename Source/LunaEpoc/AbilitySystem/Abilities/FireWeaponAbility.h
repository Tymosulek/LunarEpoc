// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "LunaGameplayAbility.h"
#include "FireWeaponAbility.generated.h"

/**
 * 
 */
UCLASS()
class LUNAEPOC_API UFireWeaponAbility : public ULunaGameplayAbility
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

public: /*Functions*/

	UFireWeaponAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) override;
	

protected: /*functions*/

	void FireWeaponLogic() const;

protected: /*properties*/
	
};