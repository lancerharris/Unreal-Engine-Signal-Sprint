// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "ASignalSprintPlayerController.generated.h"

/**
 * 
 */

class USignalSprintHUDWidget;
class ASignalSprintGameState;


UCLASS()
class SIGNALSPRINT_API AASignalSprintPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// void RefreshHUD();
	FText GetRunStateText(ASignalSprintGameState* SignalGameState) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<USignalSprintHUDWidget> HUDWidgetClass;

	UPROPERTY()
	USignalSprintHUDWidget* HUDWidgetInstance = nullptr;

	// int32 LastScore = -1;
	// int32 LastStrikes = -1;
	// float LastTimeRemaining = 0.0f;
	// FText LastRunState = FText::FromString(TEXT("State: Unknown"));
	
};
