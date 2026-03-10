// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SignalGateSpawner.generated.h"

class ASignalGate;
class ASignalSprintPlayerCharacter;

UCLASS()
class SIGNALSPRINT_API ASignalGateSpawner : public AActor
{
	GENERATED_BODY()

public:
	ASignalGateSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void TrySpawnGate();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<ASignalGate> GateClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float SpawnInterval = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float SpawnDistanceAhead = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<float> LaneOffsets = {-800.0f, 0.0f, 800.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	float SpawnZOffset = 100.0f;

	UPROPERTY()
	ASignalSprintPlayerCharacter* CachedPlayer = nullptr;

	float TimeUntilNextSpawn = 0.0f;
};
