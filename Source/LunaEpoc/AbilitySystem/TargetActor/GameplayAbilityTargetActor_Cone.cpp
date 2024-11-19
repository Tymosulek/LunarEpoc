// Project Luna Epoch
// Craig Palmer


#include "GameplayAbilityTargetActor_Cone.h"

AGameplayAbilityTargetActor_Cone::AGameplayAbilityTargetActor_Cone()
{
}

void AGameplayAbilityTargetActor_Cone::ConfirmTargetingAndContinue()
{
	// Get the player's location and forward vector
	const FVector SourceLocation = StartLocation.GetTargetingTransform().GetLocation();
	const FVector ForwardVector = StartLocation.GetTargetingTransform().GetRotation().Vector();

	TArray<FOverlapResult> OverlapResults;
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(TargetingRange);

	// Perform sphere overlap
	if (GetWorld()->OverlapMultiByObjectType(
			OverlapResults, SourceLocation, FQuat::Identity,
			FCollisionObjectQueryParams(ECC_Pawn), Sphere))
	{
		TArray<TWeakObjectPtr<AActor>> ValidTargets;

		for (const FOverlapResult& Result : OverlapResults)
		{
			AActor* TargetActor = Result.GetActor();
			if (!TargetActor || TargetActor == SourceActor)
			{
				continue;
			}

			// Check if the actor is within the cone
			FVector ToTarget = TargetActor->GetActorLocation() - SourceLocation;
			if (FVector::DotProduct(ForwardVector, ToTarget.GetSafeNormal()) >= FMath::Cos(FMath::DegreesToRadians(ConeHalfAngle)))
			{
				ValidTargets.Add(TargetActor);
			}
		}

		// Create target data
		FGameplayAbilityTargetDataHandle TargetDataHandle;
		if (ValidTargets.Num() > 0)
		{
			FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
			TargetData->TargetActorArray = ValidTargets;
			TargetDataHandle.Add(TargetData);
		}

		// Pass target data back to the ability
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
	else
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
	}
}
