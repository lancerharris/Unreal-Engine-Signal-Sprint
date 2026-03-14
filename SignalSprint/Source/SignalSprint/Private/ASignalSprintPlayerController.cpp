// Fill out your copyright notice in the Description page of Project Settings.


#include "ASignalSprintPlayerController.h"
#include "UI/SignalSprintHUDWidget.h"
#include "Gameplay/SignalSprintGameState.h"
#include "Engine/World.h"
#include "UI/SignalSprintGameOverWidget.h"

void AASignalSprintPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	PrimaryActorTick.bCanEverTick = true;

	if (HUDWidgetClass) HUDWidgetInstance = CreateWidget<USignalSprintHUDWidget>(this, HUDWidgetClass);

	if (StartMenuWidgetClass)
	{
		StartMenuWidgetInstance = CreateWidget<UUserWidget>(this, StartMenuWidgetClass);
		if (StartMenuWidgetInstance) StartMenuWidgetInstance->AddToViewport();
	}
	if (GameOverWidgetClass) GameOverWidgetInstance = CreateWidget<USignalSprintGameOverWidget>(this, GameOverWidgetClass);
	
	bShowMouseCursor = true;

	GameState = GetWorld()->GetGameState<ASignalSprintGameState>();
	if (GameState)
	{
		GameState->OnGameStateChanged.AddUObject(this, &AASignalSprintPlayerController::HandleRunStateChanged);
	}
}

void AASignalSprintPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

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

void AASignalSprintPlayerController::ShowStartMenu()
{
	StartMenuWidgetInstance->SetVisibility(ESlateVisibility::Visible);
	GameOverWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	HUDWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	bShowMouseCursor = true;
}

void AASignalSprintPlayerController::ShowGameOverMenu()
{
	if (!bGameOverWidgetAdded && GameOverWidgetInstance)
	{
		GameOverWidgetInstance->AddToViewport();
		bGameOverWidgetAdded = true;
	}
	GameOverWidgetInstance->SetFinalScoreText(GameState->GetScore());
	
	StartMenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	GameOverWidgetInstance->SetVisibility(ESlateVisibility::Visible);
	HUDWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	bShowMouseCursor = true;
}

void AASignalSprintPlayerController::ShowHUD()
{
	if (!bHUDWidgetAdded && HUDWidgetInstance)
	{
		HUDWidgetInstance->AddToViewport();
		bHUDWidgetAdded = true;
	}
	
	StartMenuWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	GameOverWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	HUDWidgetInstance->SetVisibility(ESlateVisibility::Visible);
	bShowMouseCursor = false;
}

void AASignalSprintPlayerController::HandleRunStateChanged(const FGameStatePayload& GameStatePayload)
{
	if (GameStatePayload.RunState == LastRunState) return;
	LastRunState = GameStatePayload.RunState;
	
	switch (GameStatePayload.RunState)
	{
		case ESignalSprintRunState::WaitingToStart:
			ShowStartMenu();
			break;
		case ESignalSprintRunState::Running:
			ShowHUD();
			break;
		case ESignalSprintRunState::GameOver:
			ShowGameOverMenu();
			break;
		default:
			ShowStartMenu();
			break;
	}
}
