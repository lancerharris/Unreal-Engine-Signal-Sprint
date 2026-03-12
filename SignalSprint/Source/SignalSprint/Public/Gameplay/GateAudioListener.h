// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SignalGateListener.h"
#include "GameFramework/Actor.h"
#include "GateAudioListener.generated.h"

struct FSignalGateResolution;
class ASignalGate;
class USoundBase;

UCLASS()
class SIGNALSPRINT_API AGateAudioListener : public AActor, public ISignalGateListener
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGateAudioListener();

	virtual void RegisterGate(ASignalGate* Gate) override;

	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void HandleGateResolved(const FSignalGateResolution& Resolution) const;

	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* SuccessSound;

	UPROPERTY(EditAnywhere, Category="Audio")
	USoundBase* FailureSound;

	TArray<ASignalGate*> SubscribedGates;
};
