// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SignalSprintGameState.generated.h"

UENUM(BlueprintType)
enum class ESignalSprintRunState : uint8
{
	WaitingToStart UMETA(DisplayName = "Waiting to Start"),
	Running UMETA(DisplayName = "Running"),
	GameOver UMETA(DisplayName = "GameOver")
};

UCLASS()
class SIGNALSPRINT_API ASignalSprintGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASignalSprintGameState();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Run")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Run")
	void AddStrike(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Run")
	void StartRun();

	UFUNCTION(BlueprintCallable, Category = "Run")
	void EndRun();

	UFUNCTION(BlueprintPure, Category="Run")
	float GetTimeRemaining() const { return TimeRemaining; }

	UFUNCTION(BlueprintPure, Category="Run")
	int32 GetScore() const { return Score; }

	UFUNCTION(BlueprintPure, Category="Run")
	int32 GetStrikes() const { return Strikes; }

	UFUNCTION(BlueprintPure, Category="Run")
	int32 GetMaxStrikes() const { return MaxStrikes; }

	UFUNCTION(BlueprintPure, Category="Run")
	ESignalSprintRunState GetRunState() const { return RunState; }

protected:
	void UpdateRunTimer(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Run")
	float RunDuration = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Run")
	float TimeRemaining = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Run")
	int32 Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Run")
	int32 Strikes = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Run")
	int32 MaxStrikes = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Run")
	ESignalSprintRunState RunState = ESignalSprintRunState::WaitingToStart;
};
