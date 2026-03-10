// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SignalGateSpawner.h"

#include "Gameplay/SignalGate.h"
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
}

void ASignalGateSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CachedPlayer || !GateClass)
	{
		return;
	}

	TimeUntilNextSpawn -= DeltaTime;

	if (TimeUntilNextSpawn <= 0.0f)
	{
		TrySpawnGate();
		TimeUntilNextSpawn = SpawnInterval;
	}
}

void ASignalGateSpawner::TrySpawnGate()
{
	if (!CachedPlayer || !GateClass) return;
	if (LaneOffsets.Num() == 0) return;

	const FVector PlayerLocation = CachedPlayer->GetActorLocation();

	const int32 LaneIndex = FMath::RandRange(0, LaneOffsets.Num() - 1);
	const float LaneY = LaneOffsets[LaneIndex];

	FVector SpawnLocation = PlayerLocation + FVector(SpawnDistanceAhead, LaneY - PlayerLocation.Y, SpawnZOffset);
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<ASignalGate>(GateClass, SpawnLocation, SpawnRotation, SpawnParams);
}

