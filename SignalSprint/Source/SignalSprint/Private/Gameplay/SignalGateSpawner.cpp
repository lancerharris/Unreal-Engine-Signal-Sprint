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
	if (!CachedPlayer || !GateClass)
	{
		return;
	}

	const FVector PlayerLocation = CachedPlayer->GetActorLocation();

	const float RandomY = FMath::FRandRange(-LaneHalfWidth, LaneHalfWidth);

	FVector SpawnLocation = PlayerLocation + FVector(SpawnDistanceAhead, RandomY - PlayerLocation.Y, SpawnZOffset);
	UE_LOG(LogTemp, Warning, TEXT("Spawn gate at X=%.1f Y=%.1f Z=%.1f"),
		SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<ASignalGate>(GateClass, SpawnLocation, SpawnRotation, SpawnParams);
}

