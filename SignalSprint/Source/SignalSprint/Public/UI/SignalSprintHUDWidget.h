#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SignalSprintHUDWidget.generated.h"

class UTextBlock;

UCLASS()
class SIGNALSPRINT_API USignalSprintHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="HUD")
	void SetScoreDisplay(int32 NewScore);

	UFUNCTION(BlueprintCallable, Category="HUD")
	void SetStrikesDisplay(int32 CurrentStrikes, int32 MaxStrikes);

	UFUNCTION(BlueprintCallable, Category="HUD")
	void SetTimerDisplay(float SecondsRemaining);

	UFUNCTION(BlueprintCallable, Category="HUD")
	void SetStateDisplay(const FText& StateLabel);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StrikesText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StateText;
};