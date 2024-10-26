#include "UI/ScoreWidget.h"
#include "Components/TextBlock.h"

void UScoreWidget::UpdateScore(uint32 score1, uint32 score2)
{	
	FNumberFormattingOptions FormattingOptions = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	Score1->SetText(FText::AsNumber(score1, &FormattingOptions));
	Score2->SetText(FText::AsNumber(score2, &FormattingOptions));
}
