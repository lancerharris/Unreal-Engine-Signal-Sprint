// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SignalGate.h"

#include "Components/BoxComponent.h"
#include "Player/SignalSprintPlayerCharacter.h"
#include "Gameplay/SignalSprintGameState.h"


// Sets default values
ASignalGate::ASignalGate()
{
	PrimaryActorTick.bCanEverTick = false;
	InitialLifeSpan = 15.0f;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	LeftPillar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftPillar"));
	LeftPillar->SetupAttachment(SceneRoot);
	LeftPillar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RightPillar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightPillar"));
	RightPillar->SetupAttachment(SceneRoot);
	RightPillar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TopBar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopBar"));
	TopBar->SetupAttachment(SceneRoot);
	TopBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(SceneRoot);
	TriggerBox->SetBoxExtent(FVector(100.0f, 400.0f, 200.0f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

void ASignalGate::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASignalGate::HandleTriggerOverlap);
}

void ASignalGate::HandleTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bHasBeenTriggered) return;
	if (ASignalSprintPlayerCharacter* PlayerCharacter = Cast<ASignalSprintPlayerCharacter>(OtherActor))
	{
		bHasBeenTriggered = true;
		ProcessPlayerPassedGate(PlayerCharacter);
	}

}

void ASignalGate::ProcessPlayerPassedGate(ASignalSprintPlayerCharacter* PlayerCharacter)
{
	FSignalGateResolution GateResolution;
	GateResolution.Player = PlayerCharacter;
	GateResolution.Result = GateResult;
	if (GateResult == ESignalGateResult::Success)
	{
		GateResolution.Amount = 2;
	} else if (GateResult == ESignalGateResult::Failure)
	{
		GateResolution.Amount = 1;
	}
	GateResolution.Gate = this;
	OnGateResolved.Broadcast(GateResolution);
}
