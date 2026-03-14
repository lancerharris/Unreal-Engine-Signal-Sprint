// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SignalSprintGameOverWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SIGNALSPRINT_API USignalSprintGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetFinalScoreText(int32 FinalScore);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* FinalScoreText;

};
