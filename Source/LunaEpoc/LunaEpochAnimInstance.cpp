// Fill out your copyright notice in the Description page of Project Settings.


#include "LunaEpochAnimInstance.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

ULunaEpochAnimInstance::ULunaEpochAnimInstance()
{

}

void ULunaEpochAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    // Assuming you have a reference to the owning actor and it is a character
    AActor* Owner = GetOwningActor();

    ACharacter* OwningCharacter = Cast<ACharacter>(Owner);
    if (!OwningCharacter)
    {
        // Handle the case where the owning actor is not a character
        return;
    }

    // Get the character's velocity
    FVector Velocity = OwningCharacter->GetVelocity();
    Speed = Velocity.Size();


    // Calculate direction using adjusted forward vector and velocity
    if (!Velocity.IsNearlyZero())
    {
        // Get the character's forward vector
        FVector CharacterForward = OwningCharacter->GetActorForwardVector();

        // Normalize the velocity to get the direction
        FVector Direction = Velocity.GetSafeNormal();

        // Calculate the signed angle between character's forward vector and movement direction
        float MovementDegrees = FMath::Atan2(Direction.Y, Direction.X) * 180.0f / PI;
        float CharacterFacingDegrees = FMath::Atan2(CharacterForward.Y, CharacterForward.X) * 180.0f / PI;

        // Calculate the angle difference
        float AdjustedDegrees = CharacterFacingDegrees - MovementDegrees;

        // Ensure the adjusted degrees are within [-180, 180) range
        AdjustedDegrees = FMath::Fmod(AdjustedDegrees + 180.0f, 360.0f) - 180.0f;

        // Prevent jumping from 270 to -90
        if (AdjustedDegrees < -180.0f)
        {
            AdjustedDegrees += 360.0f;
        }
        else if (AdjustedDegrees > 180.0f)
        {
            AdjustedDegrees -= 360.0f;
        }

        DirectionDegrees = AdjustedDegrees;

        // Display the adjusted degrees on screen for debugging
       // FString DebugText = FString::Printf(TEXT("Direction Degrees: %.2f"), DirectionDegrees);
       // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugText);

    }
}
