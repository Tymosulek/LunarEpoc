// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightCycleActor.generated.h"

UCLASS()
class LUNAEPOC_API ADayNightCycleActor : public AActor
{
	GENERATED_BODY()

public: /*Designer Facing Tunable*/

	//Smaller this value, faster each day will be. 
	UPROPERTY(EditAnywhere, Category = "Day Night Cycle")
	float DayLengthInSeconds = 600.f;

	//Need to debug why changing this not making a difference.
	UPROPERTY(EditAnywhere, Category = "Day Night Cycle")
	float SunriseHour = 6.0f;

	//Need to debug why changing this not making a difference.
	UPROPERTY(EditAnywhere, Category = "Day Night Cycle")
	float SunsetHour = 19.0f;


public: /*Functions*/

	ADayNightCycleActor();
	virtual void Tick(float DeltaTime) override;

public: /*Properties*/

protected: /*functions*/

	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateTimeOfDay() const;

	UFUNCTION()
	void UpdateSunDirection() const;

	UFUNCTION()
	static void UpdateLighting();

protected: /*properties*/

	UPROPERTY(BlueprintReadOnly, Category = "Day Night Cycle")
	float NormalizedTimeOfDay = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Day Night Cycle")
	UDirectionalLightComponent* SunLightComponent = nullptr;

};
