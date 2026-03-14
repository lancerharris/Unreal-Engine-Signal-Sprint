#include "Gameplay/GateVFXListener.h"

#include "Core/SignalTypes.h"
#include "Gameplay/SignalGate.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

AGateVFXListener::AGateVFXListener()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGateVFXListener::RegisterGate(ASignalGate* Gate)
{
	if (!IsValid(Gate)) return;

	SubscribedGates.AddUnique(Gate);
	Gate->OnGateResolved.AddUObject(this, &AGateVFXListener::HandleGateResolved);
}

void AGateVFXListener::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SubscribedGates.Empty();
	Super::EndPlay(EndPlayReason);
}

void AGateVFXListener::HandleGateResolved(const FSignalGateResolution& Resolution)
{
	if (!IsValid(Resolution.Gate))
	{
		return;
	}

	UNiagaraSystem* EffectToSpawn = nullptr;

	switch (Resolution.Result)
	{
	case ESignalGateResult::Success:
		EffectToSpawn = SuccessEffect;
		break;

	case ESignalGateResult::Failure:
		EffectToSpawn = FailureEffect;
		break;

	default:
		break;
	}

	if (!EffectToSpawn)
	{
		return;
	}

	const FVector SpawnLocation = Resolution.Gate->GetActorLocation() + SpawnOffset;
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		EffectToSpawn,
		SpawnLocation,
		SpawnRotation,
		SpawnScale,
		true,
		true,
		ENCPoolMethod::AutoRelease,
		true
	);
}