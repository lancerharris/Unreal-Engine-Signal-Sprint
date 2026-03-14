// Fill out your copyright notice in the Description page of Project Settings.


#include "ASignalSprintPlayerController.h"
#include "UI/SignalSprintHUDWidget.h"
#include "Gameplay/SignalSprintGameState.h"
#include "Engine/World.h"

void AASignalSprintPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = false;
	PrimaryActorTick.bCanEverTick = true;

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<USignalSprintHUDWidget>(this, HUDWidgetClass);

		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
		}
	}

	// RefreshHUD();
}

void AASignalSprintPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// RefreshHUD();
}

// void AASignalSprintPlayerController::RefreshHUD()
// {
// 	if (!HUDWidgetInstance)
// 	{
// 		return;
// 	}
//
// 	ASignalSprintGameState* SignalGameState = GetWorld()->GetGameState<ASignalSprintGameState>();
// 	if (!SignalGameState) return;
//
// 	const int32 NewScore = SignalGameState->GetScore();
// 	const int32 NewStrikes = SignalGameState->GetStrikes();
// 	const float NewTimeRemaining = SignalGameState->GetTimeRemaining();
// 	const FText NewRunState = GetRunStateText(SignalGameState);
//
// 	if (NewScore != LastScore)
// 	{
// 		LastScore = NewScore;
// 		HUDWidgetInstance->SetScoreDisplay(NewScore);
// 	}
//
// 	if (NewStrikes != LastStrikes)
// 	{
// 		LastStrikes = NewStrikes;
// 		HUDWidgetInstance->SetStrikesDisplay(NewStrikes, SignalGameState->GetMaxStrikes());
// 	}
// 	
// 	if (NewTimeRemaining != LastTimeRemaining)
// 	{
// 		LastTimeRemaining = NewTimeRemaining;
// 		HUDWidgetInstance->SetTimerDisplay(NewTimeRemaining);
// 	}
// 	
// 	if (!NewRunState.ToString().Equals(LastRunState.ToString()))
// 	{
// 		LastRunState = NewRunState;
// 		HUDWidgetInstance->SetStateDisplay(NewRunState);
// 	}
// }

FText AASignalSprintPlayerController::GetRunStateText(class ASignalSprintGameState* SignalGameState) const
{
	if (!SignalGameState)
	{
		return FText::FromString(TEXT("State: Unknown"));
	}

	switch (SignalGameState->GetRunState())
	{
	case ESignalSprintRunState::WaitingToStart:
		return FText::FromString(TEXT("State: Waiting"));
	case ESignalSprintRunState::Running:
		return FText::FromString(TEXT("State: Running"));
	case ESignalSprintRunState::GameOver:
		return FText::FromString(TEXT("State: Game Over"));
	default:
		return FText::FromString(TEXT("State: Unknown"));
	}
}
