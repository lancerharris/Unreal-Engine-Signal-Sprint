#pragma once

#include "CoreMinimal.h"
#include "SignalTypes.generated.h"

class ASignalSprintPlayerCharacter;
class ASignalGate;

UENUM(BlueprintType)
enum class ESignalGateResult : uint8
{
	Success UMETA(DisplayName="Success"),
	Failure UMETA(DisplayName="Failure")
};

USTRUCT(BlueprintType)
struct FSignalGateResolution
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	ESignalGateResult Result = ESignalGateResult::Success;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Amount = 0;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ASignalGate> Gate = nullptr;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ASignalSprintPlayerCharacter> Player = nullptr;

};