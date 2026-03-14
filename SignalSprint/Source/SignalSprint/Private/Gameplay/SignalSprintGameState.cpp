// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SignalSprintGameState.h"

ASignalSprintGameState::ASignalSprintGameState()
{
	PrimaryActorTick.bCanEverTick = true;

	GameStatePayload.Score = Score;
	GameStatePayload.Strikes = Strikes;
	GameStatePayload.MaxStrikes = MaxStrikes;
	GameStatePayload.TimeRemaining = TimeRemaining;
	GameStatePayload.RunState = RunState;
}

void ASignalSprintGameState::BeginPlay()
{
	Super::BeginPlay();
	StartRun();
}

void ASignalSprintGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RunState == ESignalSprintRunState::Running)
	{
		UpdateRunTimer(DeltaTime);
	}
}

void ASignalSprintGameState::AddScore(int32 Amount)
{
	if (RunState != ESignalSprintRunState::Running) return;

	Score += Amount;
	GameStatePayload.Score = Score;
	OnGameStateChanged.ExecuteIfBound(GameStatePayload);
}

void ASignalSprintGameState::AddStrike(int32 Amount)
{
	if (RunState != ESignalSprintRunState::Running) return;

	Strikes += Amount;

	GameStatePayload.Strikes = Strikes;
	GameStatePayload.MaxStrikes = MaxStrikes;
	OnGameStateChanged.ExecuteIfBound(GameStatePayload);
	
	if (Strikes >= MaxStrikes) EndRun();
	
}

void ASignalSprintGameState::StartRun()
{
	Score = 0;
	Strikes = 0;
	TimeRemaining = RunDuration;
	RunState = ESignalSprintRunState::Running;

	LastBroadcastSecond = FMath::CeilToInt(TimeRemaining);

	GameStatePayload.Score = Score;
	GameStatePayload.Strikes = Strikes;
	GameStatePayload.MaxStrikes = MaxStrikes;
	GameStatePayload.TimeRemaining = TimeRemaining;
	GameStatePayload.RunState = RunState;

	OnGameStateChanged.ExecuteIfBound(GameStatePayload);
}

void ASignalSprintGameState::EndRun()
{
	RunState = ESignalSprintRunState::GameOver;

	GameStatePayload.RunState = RunState;
	OnGameStateChanged.ExecuteIfBound(GameStatePayload);
}

void ASignalSprintGameState::UpdateRunTimer(float DeltaTime)
{
	TimeRemaining -= DeltaTime;

	if (TimeRemaining < 0.0f)
	{
		TimeRemaining = 0.0f;
	}

	const int32 CurrentDisplaySecond = FMath::CeilToInt(TimeRemaining);

	if (CurrentDisplaySecond != LastBroadcastSecond)
	{
		LastBroadcastSecond = CurrentDisplaySecond;
		GameStatePayload.TimeRemaining = CurrentDisplaySecond;
		OnGameStateChanged.ExecuteIfBound(GameStatePayload);
	}


	if (TimeRemaining <= 0.0f)
	{
		EndRun();
	}
}


