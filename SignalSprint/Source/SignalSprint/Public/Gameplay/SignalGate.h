// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/SignalTypes.h"
#include "SignalGate.generated.h"

class ASignalSprintGameState;
class ASignalSprintPlayerCharacter;
class UBoxComponent;
class UStaticMeshComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FSignalGateTriggerDelegate, const FSignalGateResolution&);

UCLASS()
class SIGNALSPRINT_API ASignalGate : public AActor
{
	GENERATED_BODY()

public:
	ASignalGate();
	
	FSignalGateTriggerDelegate OnGateResolved;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleTriggerOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void ProcessPlayerPassedGate(ASignalSprintPlayerCharacter* PlayerCharacter);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* LeftPillar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RightPillar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* TopBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gate")
	int32 ResolutionAmount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gate")
	bool bHasBeenTriggered = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gate")
	ESignalGateResult GateResult = ESignalGateResult::Success;

public:
};
