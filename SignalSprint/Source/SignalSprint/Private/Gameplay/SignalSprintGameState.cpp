// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SignalSprintGameState.h"

ASignalSprintGameState::ASignalSprintGameState()
{
	PrimaryActorTick.bCanEverTick = true;
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
}

void ASignalSprintGameState::AddStrike(int32 Amount)
{
	if (RunState != ESignalSprintRunState::Running) return;

	Strikes += Amount;
	if (Strikes >= MaxStrikes) EndRun();	
}

void ASignalSprintGameState::StartRun()
{
	Score = 0;
	Strikes = 0;
	RunState = ESignalSprintRunState::Running;
}

void ASignalSprintGameState::EndRun()
{
	RunState = ESignalSprintRunState::GameOver;
}

void ASignalSprintGameState::UpdateRunTimer(float DeltaTime)
{
	TimeRemaining -= DeltaTime;

	if (TimeRemaining <= 0.0f)
	{
		EndRun();
	}
}


