#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class FSPINGPONG_API APongController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PawnLeavingGame() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> PongMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	virtual void SetupInputComponent() override;
};
