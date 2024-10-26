#include "UI/PongHUD.h"

#include "Framework/PongGameState.h"
#include "UI/ScoreWidget.h"
#include "UI/GameStatusWidget.h"

void APongHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World =	GetWorld();
	if (!IsValid(World)) return;

	APlayerController* PC = GetOwningPlayerController();
	if (!IsValid(PC)) return;

	APongGameState* GameState = Cast<APongGameState>(World->GetGameState());
	if (!IsValid(GameState)) return;
	
	if (IsValid(ScoreWidgetClass.Get()))
	{
		ScoreWidget = CreateWidget<UScoreWidget>(PC, ScoreWidgetClass);
		if (IsValid(ScoreWidget))
		{
			ScoreWidget->AddToViewport(0);
			GameState->OnPlayersScoreUpdated.AddUObject(ScoreWidget, &UScoreWidget::UpdateScore);
		}		
	}

	if (IsValid(GameStatusWidgetClass.Get()))
	{
		GameStatusWidget = CreateWidget<UGameStatusWidget>(PC, GameStatusWidgetClass);
		if (IsValid(GameStatusWidget))
		{
			GameStatusWidget->AddToViewport(0);
			GameStatusWidget->SetVisibility(ESlateVisibility::Collapsed);
			GameState->OnGameStateChanged.AddWeakLambda<UGameStatusWidget>(GameStatusWidget,
				[GameStatusWidget=GameStatusWidget](bool bIsWaiting)
			{
				GameStatusWidget->SetVisibility(bIsWaiting ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
			});
		}
	}
}