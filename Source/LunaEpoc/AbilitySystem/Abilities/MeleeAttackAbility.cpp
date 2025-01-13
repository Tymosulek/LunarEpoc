// Project Luna Epoch 


#include "MeleeAttackAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void UMeleeAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Character)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	FVector Start = Character->GetActorLocation();
	FVector ForwardVector = Character->GetActorForwardVector();
	FVector End = Start + ForwardVector * MeleeRange;

	TArray<AActor*> HitActors;
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(Character);

#if WITH_EDITOR
	UKismetSystemLibrary::DrawDebugSphere(Character->GetWorld(), End, MeleeRadius, 12, FLinearColor::Red, 5.0f);
#endif

	UKismetSystemLibrary::SphereOverlapActors(
		Character->GetWorld(),
		End,
		MeleeRadius,
		ObjectTypes,
		nullptr,
		IgnoredActors,
		HitActors
	);

	for (AActor* HitActor : HitActors)
	{
		if (ShouldApplyDamageToActor(HitActor))
		{
			ApplyDamageToActor(HitActor, ActorInfo);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	
}

bool UMeleeAttackAbility::ShouldApplyDamageToActor(AActor* Actor) const
{
	if(!Actor || Actor == GetAvatarActorFromActorInfo())
	{
		return false;
	}
	
	//I will leave this right now in case we want to do more complex stuff in the future
	return true;
}

void UMeleeAttackAbility::ApplyDamageToActor(AActor* HitActor, const FGameplayAbilityActorInfo* ActorInfo)
{
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(HitActor);
	if (AbilitySystemInterface)
	{
		UAbilitySystemComponent* ASC = AbilitySystemInterface->GetAbilitySystemComponent();
		if (ASC && DamageEffectClass)
		{
			FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, DamageEffectLevel, EffectContext);
			if (SpecHandle.IsValid())
			{
				ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}
