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
