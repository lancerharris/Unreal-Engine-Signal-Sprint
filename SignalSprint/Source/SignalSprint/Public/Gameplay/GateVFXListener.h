#pragma once

#include "CoreMinimal.h"
#include "SignalGateListener.h"
#include "GameFramework/Actor.h"
#include "GateVFXListener.generated.h"

struct FSignalGateResolution;
class ASignalGate;
class UNiagaraSystem;

UCLASS()
class SIGNALSPRINT_API AGateVFXListener : public AActor, public ISignalGateListener
{
	GENERATED_BODY()

public:
	AGateVFXListener();

	virtual void RegisterGate(ASignalGate* Gate) override;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void HandleGateResolved(const FSignalGateResolution& Resolution);

protected:
	UPROPERTY(EditAnywhere, Category="VFX")
	UNiagaraSystem* SuccessEffect = nullptr;

	UPROPERTY(EditAnywhere, Category="VFX")
	UNiagaraSystem* FailureEffect = nullptr;

	UPROPERTY(EditAnywhere, Category="VFX")
	FVector SpawnOffset = FVector(0.0f, 0.0f, 100.0f);

	UPROPERTY(EditAnywhere, Category="VFX")
	FVector SpawnScale = FVector(1.0f, 1.0f, 1.0f);

	TArray<ASignalGate*> SubscribedGates;
};