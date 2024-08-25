// Project Luna Epoch 


#include "LunaCharacterMovementComponent.h"
#include "GameFramework/Character.h"

ULunaCharacterMovementComponent::ULunaCharacterMovementComponent()
{
	// Configure character movement
	RotationRate = FRotator(0.f, 640.f, 0.f);
	bConstrainToPlane = true;
	bSnapToPlaneAtStart = true;
}

void ULunaCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	CachedMaxWalkSpeed = MaxWalkSpeed;
}

void ULunaCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float TargetSpeed = CachedMaxWalkSpeed * SpeedModifier();
	if (!FMath::IsNearlyEqual(CurrentSpeed, TargetSpeed, 1.0f))
	{
		InterpolateSpeed(TargetSpeed, DeltaTime);
	}

}

void ULunaCharacterMovementComponent::InterpolateSpeed(float TargetSpeed, float DeltaTime)
{
	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, TargetSpeed, DeltaTime, InterpolationSpeed);
	MaxWalkSpeed = CurrentSpeed;
}

float ULunaCharacterMovementComponent::SpeedModifier() const
{
	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (!Owner) return 1.0f;

	FVector PlayerForward = Owner->GetActorForwardVector();
	FVector MovementInput = Owner->GetLastMovementInputVector();

	if (!PlayerForward.Normalize() || !MovementInput.Normalize()) return 1.0f;

	//Modify speed to 50% if moving backwards.
	constexpr float BackwardThreshold = -0.6f;
	return (FVector::DotProduct(PlayerForward, MovementInput) < BackwardThreshold) ? 0.5f : 1.0f;
}
