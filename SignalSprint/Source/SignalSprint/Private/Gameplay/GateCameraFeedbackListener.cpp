#include "Gameplay/GateCameraFeedbackListener.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Core/SignalTypes.h"
#include "Gameplay/SignalGate.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Player/SignalSprintPlayerCharacter.h"

AGateCameraFeedbackListener::AGateCameraFeedbackListener()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGateCameraFeedbackListener::BeginPlay()
{
	Super::BeginPlay();

	CachedPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (ASignalSprintPlayerCharacter* PlayerCharacter = Cast<ASignalSprintPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		CachedCameraComponent = PlayerCharacter->FindComponentByClass<UCameraComponent>();

		if (CachedCameraComponent)
		{
			BaseFOV = CachedCameraComponent->FieldOfView;
		}
	}
}

void AGateCameraFeedbackListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CachedCameraComponent)
	{
		return;
	}

	CurrentFOVOffset = FMath::FInterpTo(CurrentFOVOffset, 0.0f, DeltaTime, FOVPunchDecaySpeed);

	const float TargetFOV = BaseFOV + CurrentFOVOffset;
	const float NewFOV = FMath::FInterpTo(CachedCameraComponent->FieldOfView, TargetFOV, DeltaTime, FOVReturnSpeed);

	CachedCameraComponent->SetFieldOfView(NewFOV);
}

void AGateCameraFeedbackListener::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SubscribedGates.Empty();
	Super::EndPlay(EndPlayReason);
}

void AGateCameraFeedbackListener::RegisterGate(ASignalGate* Gate)
{
	if (!IsValid(Gate)) return;

	SubscribedGates.AddUnique(Gate);
	Gate->OnGateResolved.AddUObject(this, &AGateCameraFeedbackListener::HandleGateResolved);
}

void AGateCameraFeedbackListener::HandleGateResolved(const FSignalGateResolution& Resolution)
{
	switch (Resolution.Result)
	{
	case ESignalGateResult::Success:
		TriggerSuccessFeedback();
		break;

	case ESignalGateResult::Failure:
		TriggerFailureFeedback();
		break;

	default:
		break;
	}
}

void AGateCameraFeedbackListener::TriggerSuccessFeedback()
{
	if (CachedPlayerController && SuccessCameraShakeClass)
	{
		CachedPlayerController->ClientStartCameraShake(SuccessCameraShakeClass);
	}

	ApplyFOVPunch(SuccessFOVPunchAmount);
}

void AGateCameraFeedbackListener::TriggerFailureFeedback()
{
	if (CachedPlayerController && FailureCameraShakeClass)
	{
		CachedPlayerController->ClientStartCameraShake(FailureCameraShakeClass);
	}

	ApplyFOVPunch(FailureFOVPunchAmount);
}

void AGateCameraFeedbackListener::ApplyFOVPunch(float Amount)
{
	CurrentFOVOffset = FMath::Max(CurrentFOVOffset, Amount);
}