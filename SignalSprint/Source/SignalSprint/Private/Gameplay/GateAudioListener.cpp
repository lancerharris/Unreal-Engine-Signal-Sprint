// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GateAudioListener.h"

#include "Gameplay/SignalGate.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGateAudioListener::AGateAudioListener()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGateAudioListener::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGateAudioListener::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (ASignalGate* Gate : SubscribedGates)
	{
		if (IsValid(Gate))
		{
			Gate->OnGateResolved.RemoveAll(this);
		}
	}

	SubscribedGates.Empty();
}

void AGateAudioListener::RegisterGate(ASignalGate* Gate)
{
	if (!IsValid(Gate)) return;

	SubscribedGates.AddUnique(Gate);

	Gate->OnGateResolved.AddUObject(this, &AGateAudioListener::HandleGateResolved);
}

void AGateAudioListener::HandleGateResolved(const FSignalGateResolution& Resolution) const
{
	switch (Resolution.Result)
	{
	case ESignalGateResult::Success:
		if (SuccessSound)
		{
			UGameplayStatics::PlaySound2D(this, SuccessSound);
		}
		break;

	case ESignalGateResult::Failure:
		if (FailureSound)
		{
			UGameplayStatics::PlaySound2D(this, FailureSound);
		}
		break;
	}
}

