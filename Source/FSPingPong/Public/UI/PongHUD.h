#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PongHUD.generated.h"

class UGameStatusWidget;
class UScoreWidget;

UCLASS()
class FSPINGPONG_API APongHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameStatusWidget> GameStatusWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UScoreWidget> ScoreWidget;
	
	UPROPERTY()
	TObjectPtr<UGameStatusWidget> GameStatusWidget;
};
