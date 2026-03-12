#pragma once

#include "CoreMinimal.h"
#include "SignalGateListener.h"
#include "GameFramework/Actor.h"
#include "GateCameraFeedbackListener.generated.h"

struct FSignalGateResolution;
class ASignalGate;
class APlayerController;
class UCameraComponent;

UCLASS()
class SIGNALSPRINT_API AGateCameraFeedbackListener : public AActor, public ISignalGateListener
{
	GENERATED_BODY()

public:
	AGateCameraFeedbackListener();

	virtual void RegisterGate(ASignalGate* Gate) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void HandleGateResolved(const FSignalGateResolution& Resolution);

	void TriggerSuccessFeedback();
	void TriggerFailureFeedback();

	void ApplyFOVPunch(float Amount);

protected:
	UPROPERTY(EditAnywhere, Category="Camera Feedback|Shake")
	TSubclassOf<UCameraShakeBase> SuccessCameraShakeClass;

	UPROPERTY(EditAnywhere, Category="Camera Feedback|Shake")
	TSubclassOf<UCameraShakeBase> FailureCameraShakeClass;

	UPROPERTY(EditAnywhere, Category="Camera Feedback|FOV")
	float BaseFOV = 90.0f;

	UPROPERTY(EditAnywhere, Category="Camera Feedback|FOV")
	float SuccessFOVPunchAmount = 4.0f;

	UPROPERTY(EditAnywhere, Category="Camera Feedback|FOV")
	float FailureFOVPunchAmount = 8.0f;

	UPROPERTY(EditAnywhere, Category="Camera Feedback|FOV")
	float FOVReturnSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category="Camera Feedback|FOV")
	float FOVPunchDecaySpeed = 14.0f;

	UPROPERTY()
	APlayerController* CachedPlayerController = nullptr;

	UPROPERTY()
	UCameraComponent* CachedCameraComponent = nullptr;

	TArray<ASignalGate*> SubscribedGates;

	float CurrentFOVOffset = 0.0f;
};