// Project Luna Epoch 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LunaWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

public:

	FWidgetControllerParams() {};
	FWidgetControllerParams(APlayerController* Pc, APlayerState* Ps, UAbilitySystemComponent* Asc, UAttributeSet* As)
		: PlayerController(Pc),
		PlayerState(Ps),
		AbilitySystemComponent(Asc),
		AttributeSet(As) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

};

UCLASS()
class LUNAEPOC_API ULunaWidgetController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	virtual void BroadcastInitialValues();

	virtual void BindCallbacksToDependancies();

protected:
	UPROPERTY(BlueprintReadOnly, Category = WidgetController)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = WidgetController)
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = WidgetController)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = WidgetController)
	TObjectPtr<UAttributeSet> AttributeSet;
	
};