// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AWeapon.generated.h"

UCLASS()
class LUNAEPOC_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public: /*Designer Facing Tunable*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    int32 AmmoCount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    int32 MaxAmmo = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    float Damage = 50.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    USkeletalMeshComponent* WeaponMesh = nullptr;

public: /*Functions*/

	AWeapon();

	void Fire();
	void Reload();
};
