// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SignalGateSpawner.h"

#include "Core/SignalTypes.h"
#include "Gameplay/GateAudioListener.h"
#include "Gameplay/GateCameraFeedbackListener.h"
#include "Gameplay/GateVFXListener.h"
#include "Gameplay/SignalGate.h"
#include "Gameplay/SignalSprintGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SignalSprintPlayerCharacter.h"

ASignalGateSpawner::ASignalGateSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASignalGateSpawner::BeginPlay()
{
	Super::BeginPlay();

	CachedPlayer = Cast<ASignalSprintPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	TimeUntilNextSpawn = SpawnInterval;

	GameState = GetWorld()->GetGameState<ASignalSprintGameState>();
	if (GameState)
	{
		GameState->OnGameStateChanged.AddUObject(this, &ASignalGateSpawner::HandleGameStateChanged);
	}
}

void ASignalGateSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CachedPlayer || GateClasses.Num() == 0)
	{
		return;
	}

	if (LastRunState != ESignalSprintRunState::Running) return;
	
	TimeUntilNextSpawn -= DeltaTime;

	if (TimeUntilNextSpawn <= 0.0f)
	{
		TrySpawnGate();
		TimeUntilNextSpawn = SpawnInterval;
	}
}

void ASignalGateSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GameState) GameState->OnGameStateChanged.RemoveAll(this);
	SubscribedGates.Empty();
	Super::EndPlay(EndPlayReason);
}

void ASignalGateSpawner::TrySpawnGate()
{
	if (!CachedPlayer || GateClasses.Num() == 0) return;
	if (LaneOffsets.Num() == 0) return;

	const int32 GateClassIndex = FMath::RandRange(0, GateClasses.Num() - 1);
	TSubclassOf<ASignalGate> SelectedGateClass = GateClasses[GateClassIndex];
	
	const FVector PlayerLocation = CachedPlayer->GetActorLocation();

	const int32 LaneIndex = FMath::RandRange(0, LaneOffsets.Num() - 1);
	const float LaneY = LaneOffsets[LaneIndex];

	FVector SpawnLocation = PlayerLocation + FVector(SpawnDistanceAhead, LaneY - PlayerLocation.Y, SpawnZOffset);
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ASignalGate* SpawnedGate = GetWorld()->SpawnActor<ASignalGate>(SelectedGateClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (!SpawnedGate) return;
	SubscribedGates.AddUnique(SpawnedGate);
	SpawnedGate->OnGateResolved.AddUObject(this, &ASignalGateSpawner::ProcessGateResolutionPayload);
	for (AActor* ListenerActor : GateListeners)
	{
		if (!IsValid(ListenerActor))
		{
			continue;
		}

		if (ISignalGateListener* GateListener = Cast<ISignalGateListener>(ListenerActor))
		{
			GateListener->RegisterGate(SpawnedGate);
		}
	}
}

void ASignalGateSpawner::ProcessGateResolutionPayload(const FSignalGateResolution& Resolution)
{
	if (!GameState) return;
	if (Resolution.Result == ESignalGateResult::Success)
	{
		GameState->AddScore(Resolution.Amount);
	} else if (Resolution.Result == ESignalGateResult::Failure)
	{
		GameState->AddStrike(Resolution.Amount);
	}
}

void ASignalGateSpawner::HandleGameStateChanged(const FGameStatePayload& GameStatePayload)
{
	if (LastRunState == GameStatePayload.RunState) return;
	LastRunState = GameStatePayload.RunState;
}

