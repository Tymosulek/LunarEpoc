// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AudioOcclusionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUNAEPOC_API UAudioOcclusionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	float TracerRange{};

	UPROPERTY(BlueprintReadOnly);
	float OcclusionPercentage{0.f};

	UPROPERTY(BlueprintReadOnly)
	bool IsActorAudioOccluded{false};

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> OcclusionMaterials{};

private:
	
	FTimerHandle OcclusionTimerHandle{};

public:

	//Test Function
	UFUNCTION(BlueprintCosmetic,BlueprintCallable)
	bool IsActorInLightCone(float VisionAngle, float VisionRange);

protected:
	
	virtual void BeginPlay() override;
	void DoAudioOcclusionLogic();

public:
	UAudioOcclusionComponent();
	
};
