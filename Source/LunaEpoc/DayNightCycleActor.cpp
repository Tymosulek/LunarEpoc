// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycleActor.h"
#include "Engine/DirectionalLight.h"
#include "Kismet/GameplayStatics.h" 
#include "Components/DirectionalLightComponent.h"

ADayNightCycleActor::ADayNightCycleActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADayNightCycleActor::BeginPlay()
{
	Super::BeginPlay();


    // Find and set the existing directional light component in the level
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), FoundActors);

    if (FoundActors.Num() > 0)
    {
        SunLightComponent = Cast<UDirectionalLightComponent>(FoundActors[0]->GetComponentByClass(UDirectionalLightComponent::StaticClass()));
    }

    check(SunLightComponent);

	UpdateTimeOfDay();	
}

void ADayNightCycleActor::UpdateTimeOfDay()
{
    // Implement logic to update any other time-dependent parameters if needed

    int32 TimeInSeconds = static_cast<int32>((NormalizedTimeOfDay * 86400.0f));
    FTimespan Timespan(0, 0, TimeInSeconds);
    UE_LOG(LogTemp, Warning, TEXT("Time: %02d:%02d:%02d"), Timespan.GetHours(), Timespan.GetMinutes(), Timespan.GetSeconds());
}

void ADayNightCycleActor::UpdateSunDirection()
{
    // Calculate the total number of hours in a day
    float TotalHoursInDay = SunsetHour - SunriseHour;

    // Calculate the sun angle based on the normalized time of day
    float SunAngle = ((NormalizedTimeOfDay - SunsetHour / 24.0f) + 1.0f) * 360.0f;
    SunAngle = FMath::Fmod(SunAngle, 360.0f); // Ensure the angle stays within the range [0, 360)

    FRotator NewSunRotation = FRotator(SunAngle, 0.0f, 0.0f);
    SunLightComponent->SetWorldRotation(NewSunRotation);
}

void ADayNightCycleActor::UpdateLighting()
{
    // Implement logic to update lighting parameters based on time of day
}

// Called every frame
void ADayNightCycleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Update time of day
    NormalizedTimeOfDay += DeltaTime / DayLengthInSeconds;

    if (NormalizedTimeOfDay > 1.0f)
    {
        NormalizedTimeOfDay = 0.0f;
    }

    UpdateTimeOfDay();
    UpdateSunDirection();
    UpdateLighting();
}

