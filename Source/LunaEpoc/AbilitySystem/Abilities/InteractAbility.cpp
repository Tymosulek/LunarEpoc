// Project Luna Epoch 


#include "InteractAbility.h"

#include "Components/SphereComponent.h"
#include "LunaEpoc/LunaCharacter.h"
#include "LunaEpoc/Inventory/Interactable.h"

bool UInteractAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayTagContainer* SourceTags,
                                          const FGameplayTagContainer* TargetTags,
                                          FGameplayTagContainer* OptionalRelevantTags) const
{
	ALunaCharacter* Player = Cast<ALunaCharacter>(ActorInfo->AvatarActor.Get());
	if (!Player)
	{
		return false;
	}

	// Check for interactable objects in range
	TArray<AActor*> Interactables;
	if (!FindInteractableInRange(Player, Interactables, InteractionRadius))
	{
		return false;
	}

	return CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UInteractAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// Get the player character
	ALunaCharacter* Player = Cast<ALunaCharacter>(GetAvatarActorFromActorInfo());
	if (!Player)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// Find interactable objects and interact with them
	TArray<AActor*> Interactables;
	if (FindInteractableInRange(Player, Interactables, InteractionRadius))
	{
		for (AActor* Interactable : Interactables)
		{
			if (Interactable->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{
				if (IInteractable* InteractableInterface = Cast<IInteractable>(Interactable))
				{
					InteractableInterface->Interact(Player);
				}
			}
		}
	}

	K2_EndAbility();
}

bool UInteractAbility::FindInteractableInRange(const ALunaCharacter* Player, TArray<AActor*>& OutInteractables, const float Range)
{
	if (!Player || !Player->InteractionCollider)
	{
		return false;
	}
	
	// Check for overlapping actors using the collider
	TArray<AActor*> OverlappingActors;
	Player->InteractionCollider->GetOverlappingActors(OverlappingActors);

	bool bFoundInteractable = false;

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor == Player) continue;
		
		if (Actor && Actor->Implements<UInteractable>())
		{
			OutInteractables.Add(Actor);
			bFoundInteractable = true;
		}
	}

	return bFoundInteractable;
}
