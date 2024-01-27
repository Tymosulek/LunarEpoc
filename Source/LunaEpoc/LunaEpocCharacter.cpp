// Copyright Epic Games, Inc. All Rights Reserved.

#include "LunaEpocCharacter.h"

#include "LunaEpocAttributeSet.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"

ALunaEpocCharacter::ALunaEpocCharacter()
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

	//Ability System Component Creation
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	//Attribute Set Creation
	Attributes = CreateDefaultSubobject<ULunaEpocAttributeSet>(TEXT("AttributeSet"));
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

void ALunaEpocCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	InitializeAttributes();
	GiveDefaultAbilities();
}

void ALunaEpocCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	InitializeAttributes();
}

void ALunaEpocCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ALunaEpocCharacter::GiveDefaultAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (auto& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(), 1, 0));
		}
	}
}

UAbilitySystemComponent* ALunaEpocCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
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

	// Last input vector to show which direction character is moving
	FVector MovementInput = GetLastMovementInputVector();

	// Normalize vectors to ensure accurate dot product results
	PlayerForward.Normalize();
	MovementInput.Normalize();

	// Calculate the dot product
	const float DotProduct = FVector::DotProduct(PlayerForward, MovementInput);

	// Check if the dot product is less than the backwardThreshold
	const bool bMovingBackward = DotProduct < -0.6f;

	// Now, bMovingBackward will be true if the player is moving backward
	if (bMovingBackward)
	{
		// Player is moving backward
		return 0.5f; // Apply speed modifier for backward movement
	}
	else
	{
		// Player is not moving backward
		return 1.0f; // Default speed modifier for other directions
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
