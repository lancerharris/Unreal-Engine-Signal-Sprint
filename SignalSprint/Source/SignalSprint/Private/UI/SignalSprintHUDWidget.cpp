#include "UI/SignalSprintHUDWidget.h"

#include "Components/TextBlock.h"
#include "Math/UnrealMathUtility.h"

void USignalSprintHUDWidget::SetScoreDisplay(int32 NewScore)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::Format(
			FText::FromString(TEXT("Score: {0}")),
			FText::AsNumber(NewScore)
		));
	}
}

void USignalSprintHUDWidget::SetStrikesDisplay(int32 CurrentStrikes, int32 MaxStrikes)
{
	if (StrikesText)
	{
		StrikesText->SetText(FText::Format(
			FText::FromString(TEXT("Strikes: {0} / {1}")),
			FText::AsNumber(CurrentStrikes),
			FText::AsNumber(MaxStrikes)
		));
	}
}

void USignalSprintHUDWidget::SetTimerDisplay(float SecondsRemaining)
{
	if (TimerText)
	{
		const int32 DisplaySeconds = FMath::CeilToInt(SecondsRemaining);

		TimerText->SetText(FText::Format(
			FText::FromString(TEXT("Time: {0}")),
			FText::AsNumber(DisplaySeconds)
		));
	}
}

void USignalSprintHUDWidget::SetStateDisplay(const FText& StateLabel)
{
	if (StateText)
	{
		StateText->SetText(StateLabel);
	}
}