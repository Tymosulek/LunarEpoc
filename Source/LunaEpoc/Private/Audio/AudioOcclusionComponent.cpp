#include "LunaEpoc/Public/Audio/AudioOcclusionComponent.h"

UAudioOcclusionComponent::UAudioOcclusionComponent()
{

	PrimaryComponentTick.bCanEverTick = false;


}

bool UAudioOcclusionComponent::IsActorInLightCone(float VisionAngle, float VisionRange)
{
	const AActor* OwnerActor = Cast<AActor>(GetOwner());
	const UWorld* World = OwnerActor->GetWorld();

	if(!OwnerActor || !World )
	{
		return false;
	}

	FVector Location = OwnerActor->GetActorLocation();
	FVector LocationForward = OwnerActor->GetActorForwardVector();

	float CosVisionAngle = FMath::Cos(FMath::DegreesToRadians(VisionAngle/2.f));

	TArray<FOverlapResult> Overlaps;
	FCollisionShape VisionSphere = FCollisionShape::MakeSphere(VisionRange);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerActor);

	bool bHit = World->OverlapMultiByChannel(
		Overlaps,
		Location,
		FQuat::Identity,
		ECC_Pawn,
		VisionSphere,
		QueryParams
		);

	if(bHit)
	{
		for(const FOverlapResult& OverlapResult : Overlaps)
		{
			AActor* TargetActor = OverlapResult.GetActor();
			if(TargetActor)
			{
				FVector DirectionToTarget = (TargetActor->GetActorLocation() - Location).GetSafeNormal();
				float DotProduct = FVector::DotProduct(LocationForward, DirectionToTarget);

				if(DotProduct >= CosVisionAngle)
				{
					return true;
				}
				
			}
		}
	}

	return false;
	
}

void UAudioOcclusionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if(GetOwner() && GetOwner()->GetWorld())
	{
		GetOwner()->GetWorld()->GetTimerManager().SetTimer(
			OcclusionTimerHandle,
			this,
			&UAudioOcclusionComponent::DoAudioOcclusionLogic,
			0.5f,
			true
			);
	}
}

void UAudioOcclusionComponent::DoAudioOcclusionLogic()
{

	//Check if we have an Owner
	const AActor* OwnerActor = Cast<AActor>(GetOwner());

	if(!OwnerActor)
	{
		return;
	}

	const FVector ActorLocation = OwnerActor->GetActorLocation();
	
	TArray Directions =
		{
		OwnerActor->GetActorForwardVector(),
		-OwnerActor->GetActorForwardVector(),
		OwnerActor->GetActorRightVector(),
		-OwnerActor->GetActorRightVector(),
		};

	//Setting up for Tracer
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(OwnerActor);

	int32 HitCount{0};
	FHitResult HitResult;

	for(const FVector& Direction : Directions)
	{
		FVector EndLocation = ActorLocation + (Direction * TracerRange);

		if(GetWorld()->LineTraceSingleByChannel(HitResult, ActorLocation, EndLocation, ECC_Visibility, CollisionParams))
		{
			UMaterialInterface* HitMaterial = HitResult.GetComponent() ? HitResult.GetComponent()->GetMaterial(0) : nullptr;

			if(HitMaterial && OcclusionMaterials.Contains(HitMaterial))
			{
				HitCount++;
#if WITH_EDITOR
				DrawDebugLine(GetWorld(), ActorLocation, HitResult.Location, FColor::Red, false, -1, 0, 0.5f);
#endif
			}
			else
			{
#if WITH_EDITOR
				DrawDebugLine(GetWorld(), ActorLocation, HitResult.Location, FColor::Blue, false, -1, 0, 0.5f);
#endif
			}
		}

	}

	const float Percentage = static_cast<float>(HitCount) / Directions.Num();

	IsActorAudioOccluded  = OcclusionPercentage > 0.5f;

	OcclusionPercentage = Percentage;

#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Yellow, FString::Printf(TEXT("Occlusion Percentage: %f"), OcclusionPercentage));
#endif
}

