#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStatusWidget.generated.h"

class UTextBlock;

UCLASS()
class FSPINGPONG_API UGameStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta= (BindWidget))
	TObjectPtr<UTextBlock> GameStatus;
};
