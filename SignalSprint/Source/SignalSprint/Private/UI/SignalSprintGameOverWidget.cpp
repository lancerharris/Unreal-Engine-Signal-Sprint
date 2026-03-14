// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SignalSprintGameOverWidget.h"

#include "Components/TextBlock.h"


void USignalSprintGameOverWidget::SetFinalScoreText(int32 FinalScore)
{
	if (FinalScoreText)
	{
		FinalScoreText->SetText(FText::Format(
			FText::FromString(TEXT("Final Score: {0}")),
			FText::AsNumber(FinalScore)
		));
	}
}
