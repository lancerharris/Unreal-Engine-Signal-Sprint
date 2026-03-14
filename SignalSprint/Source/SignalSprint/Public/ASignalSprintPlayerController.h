// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/SignalTypes.h"

#include "GameFramework/PlayerController.h"
#include "Gameplay/SignalSprintGameState.h"
#include "ASignalSprintPlayerController.generated.h"

/**
 * 
 */

class USignalSprintGameOverWidget;
struct FGameStatePayload;
class USignalSprintHUDWidget;
class ASignalSprintGameState;


UCLASS()
class SIGNALSPRINT_API AASignalSprintPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	
	FText GetRunStateText(ASignalSprintGameState* SignalGameState) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<USignalSprintHUDWidget> HUDWidgetClass;

	UPROPERTY()
	USignalSprintHUDWidget* HUDWidgetInstance = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<UUserWidget> StartMenuWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<USignalSprintGameOverWidget> GameOverWidgetClass;

	UPROPERTY()
	UUserWidget* StartMenuWidgetInstance = nullptr;
	UPROPERTY()
	USignalSprintGameOverWidget* GameOverWidgetInstance = nullptr;

	ESignalSprintRunState LastRunState = ESignalSprintRunState::WaitingToStart;

	UFUNCTION()
	void ShowStartMenu();
	UFUNCTION()
	void ShowGameOverMenu();
	UFUNCTION()
	void ShowHUD();
	void HandleRunStateChanged(const FGameStatePayload& GameStatePayload);

	UPROPERTY()
	ASignalSprintGameState* GameState = nullptr;

	
	bool bGameOverWidgetAdded = false;
	bool bHUDWidgetAdded = false;

	
};
