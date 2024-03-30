// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunaCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/Material.h"
#include "Player/LunaPlayerState.h"
#include "UObject/ConstructorHelpers.h"
#include "LunaEpoc/AbilitySystem/Components/LunaAbilitySystemComponent.h"

ALunaCharacter::ALunaCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

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

void ALunaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server.
	InitAbilityActorInfo();
}

void ALunaCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client.
	InitAbilityActorInfo();
}

void ALunaCharacter::InitAbilityActorInfo()
{
	APlayerState* PS = GetPlayerState();
	ALunaPlayerState* LunaPlayerState = GetPlayerState<ALunaPlayerState>();
	check(LunaPlayerState)
	LunaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(LunaPlayerState, this);
	AbilitySystemComponent = LunaPlayerState->GetAbilitySystemComponent();
	AttributeSet = LunaPlayerState->GetAttributeSet();
}

void ALunaCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	CurrentSpeed = MaxWalkSpeed;
}

void ALunaCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Make character rotate to face mouse position.
	RotateToMouse(DeltaSeconds);

	//Gradually change the speed of character when sprinting/walking.
	float TargetSpeed = MaxWalkSpeed;
	TargetSpeed *= SpeedModifier();
	InterpolateSpeed(TargetSpeed, DeltaSeconds);
}

float ALunaCharacter::SpeedModifier() const
{
	// Get the forward vector of the player's mesh or capsule component
	FVector PlayerForward = GetActorForwardVector();

	// Last input vector to show which direction character is moving
	FVector MovementInput = GetLastMovementInputVector();

	// Normalize vectors to ensure accurate dot product results
	PlayerForward.Normalize();
	MovementInput.Normalize();

	// Calculate the dot product
	const float DotProduct = FVector::DotProduct(PlayerForward, MovementInput);

	// Check if the dot product is less than the backwardThreshold
	// will be true if the player is moving backward
	if (DotProduct < -0.6f)
	{
		// Player is moving backward
		return 0.5f; // Apply speed modifier for backward movement
	}
	
	// Player is not moving backward
	return 1.0f; // Default speed modifier for other directions
}

void ALunaCharacter::RotateToMouse(float DeltaSeconds)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		return;
	}

	FHitResult HitResult;
	FVector MouseWorldLocation;

	// Ignore the character itself
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	// Get the hit result under the cursor
	if (!PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		return;
	}

	// Extract the hit location
	MouseWorldLocation = HitResult.Location;

	// Keep the same Z-coordinate as the character
	MouseWorldLocation.Z = GetActorLocation().Z;

	FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MouseWorldLocation);

	// Interpolate rotation with the shortest path across -180/180 boundary
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationSpeed);

	SetActorRotation(NewRotation);
}

void ALunaCharacter::InterpolateSpeed(float TargetSpeed, float DeltaTime)
{
	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, TargetSpeed, DeltaTime, InterpolationSpeed);
	GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
}
