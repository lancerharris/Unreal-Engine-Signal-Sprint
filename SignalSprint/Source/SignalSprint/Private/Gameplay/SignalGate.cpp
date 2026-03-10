// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SignalGate.h"

#include "Components/BoxComponent.h"


// Sets default values
ASignalGate::ASignalGate()
{
	PrimaryActorTick.bCanEverTick = false;

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

	InitialLifeSpan = 15.0f;
}
