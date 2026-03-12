#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SignalGateListener.generated.h"

class ASignalGate;

UINTERFACE(MinimalAPI)
class USignalGateListener : public UInterface
{
	GENERATED_BODY()
};

class SIGNALSPRINT_API ISignalGateListener
{
	GENERATED_BODY()

public:
	virtual void RegisterGate(ASignalGate* Gate) = 0;
};