#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"


class UTextBlock;

UCLASS()
class FSPINGPONG_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateScore(uint32 score1, uint32 score2);

protected:
	UPROPERTY(BlueprintReadWrite, meta= (BindWidget))
	TObjectPtr<UTextBlock> Score1;

	UPROPERTY(BlueprintReadWrite, meta= (BindWidget))
	TObjectPtr<UTextBlock> Score2;
};
