// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SignalSprintGameState.h"
#include "GameFramework/Actor.h"
#include "SignalGateSpawner.generated.h"

class USignalGateListener;
class AGateVFXListener;
class AGateCameraFeedbackListener;
struct FSignalGateResolution;

class ASignalSprintGameState;
class ASignalGate;
class ASignalSprintPlayerCharacter;
class AGateAudioListener;

UCLASS()
class SIGNALSPRINT_API ASignalGateSpawner : public AActor
{
	GENERATED_BODY()

public:
	ASignalGateSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void TrySpawnGate();
	
	void ProcessGateResolutionPayload(const FSignalGateResolution& Resolution);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning")
	TArray<TSubclassOf<ASignalGate>> GateClasses;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float SpawnInterval = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float SpawnDistanceAhead = 2500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<float> LaneOffsets = {-800.0f, 0.0f, 800.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float SpawnZOffset = 100.0f;

	UPROPERTY()
	ASignalSprintPlayerCharacter* CachedPlayer = nullptr;

	float TimeUntilNextSpawn = 0.0f;

	UPROPERTY()
	ASignalSprintGameState* GameState = nullptr;

	ESignalSprintRunState LastRunState = ESignalSprintRunState::WaitingToStart;

	void HandleGameStateChanged(const FGameStatePayload& GameStatePayload);

	UPROPERTY(EditAnywhere, Category = "GateListeners")
	TArray<AActor*> GateListeners;

	TArray<ASignalGate*> SubscribedGates;
};
