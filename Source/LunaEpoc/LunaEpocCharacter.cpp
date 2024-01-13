// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunaEpocCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

ALunaEpocCharacter::ALunaEpocCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character pitch and roll, yaw is fine.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ALunaEpocCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	bShouldSprint = false;
	CurrentSpeed = MaxWalkSpeed;
}

void ALunaEpocCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Make character rotate to face mouse position.
	RotateToMouse(DeltaSeconds);

	//Gradually change the speed of character when sprinting/walking.
	float TargetSpeed = bShouldSprint ? MaxSprintSpeed : MaxWalkSpeed;
	TargetSpeed *= SpeedModifier();
	InterpolateSpeed(TargetSpeed, DeltaSeconds);
}

void ALunaEpocCharacter::Move(const FVector2D& InputVector)
{
	// Move the character forward based on the Y component of MovementVector
	AddMovementInput(FVector::ForwardVector, InputVector.Y);

	// Move the character right based on the X component of MovementVector
	AddMovementInput(FVector::RightVector, InputVector.X);
}

void ALunaEpocCharacter::SetSprint(const bool bNewSprint)
{
	bShouldSprint = bNewSprint;
}

float ALunaEpocCharacter::SpeedModifier() const
{
	// Get the forward vector of the player's mesh or capsule component
	FVector PlayerForward = GetActorForwardVector();

	// Last input vector to show which direction character is moving.
	FVector MovementInput = GetLastMovementInputVector();

	// Normalize vectors to ensure accurate dot product results
	PlayerForward.Normalize();
	MovementInput.Normalize();

	// Calculate the dot product
	const float DotProduct = FVector::DotProduct(PlayerForward, MovementInput);

	// Check if the dot product is greater than the threshold
	const bool bSameDirection = DotProduct > StrafeSpeedThreshold;

	// Now, bSameDirection will be true if the player is moving in the same direction as they are facing
	if (bSameDirection)
	{
		// Player is moving in the same direction as facing
		return 1;
	}
	else
	{
		// Player is not moving in the same direction as facing
		return 0.5;
	}
}

void ALunaEpocCharacter::RotateToMouse(float DeltaSeconds)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		return;
	}


	FHitResult Hit;
	bool bSuccess = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
	if (!bSuccess)
	{
		return;
	}

	FVector MouseLocation(Hit.Location.X, Hit.Location.Y, GetActorLocation().Z);

	FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MouseLocation);

	// Adjust the target rotation to match the character's forward vector
	//TargetRotation.Yaw += 270.0f; 

	// Interpolate rotation with shortest path across -180/180 boundary
	FRotator LerpedRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationSpeed);

	SetActorRotation(LerpedRotation);
}

void ALunaEpocCharacter::InterpolateSpeed(float TargetSpeed, float DeltaTime)
{
	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, TargetSpeed, DeltaTime, InterpolationSpeed);
	GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
}
