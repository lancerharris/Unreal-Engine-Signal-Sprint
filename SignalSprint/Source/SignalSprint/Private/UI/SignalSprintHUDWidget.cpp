#include "UI/SignalSprintHUDWidget.h"
#include "Gameplay/SignalSprintGameState.h"
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

void USignalSprintHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameState = GetWorld()->GetGameState<ASignalSprintGameState>();
	if (GameState)
	{
		GameState->OnGameStateChanged.BindUObject(this, &USignalSprintHUDWidget::HandleGameStateChanged);

		FGameStatePayload InitialPayload;
		InitialPayload.Score = GameState->GetScore();
		InitialPayload.Strikes = GameState->GetStrikes();
		InitialPayload.MaxStrikes = GameState->GetMaxStrikes();
		InitialPayload.TimeRemaining = GameState->GetTimeRemaining();
		InitialPayload.RunState = GameState->GetRunState();

		HandleGameStateChanged(InitialPayload);
	}
}

void USignalSprintHUDWidget::HandleGameStateChanged(const FGameStatePayload& GameStatePayload)
{
	if (GameState)
	{
		SetScoreDisplay(GameStatePayload.Score);
		SetStrikesDisplay(GameStatePayload.Strikes, GameStatePayload.MaxStrikes);
		SetTimerDisplay(GameStatePayload.TimeRemaining);
		switch (GameStatePayload.RunState)
		{
		case ESignalSprintRunState::Running:
			SetStateDisplay(FText::FromString(TEXT("Running")));
			break;
		case ESignalSprintRunState::GameOver:
			SetStateDisplay(FText::FromString(TEXT("Game Over")));
			break;
		case ESignalSprintRunState::WaitingToStart:
			SetStateDisplay(FText::FromString(TEXT("Waiting")));
			break;
		default:
			SetStateDisplay(FText::FromString(TEXT("Unknown")));
		}
	}
}
