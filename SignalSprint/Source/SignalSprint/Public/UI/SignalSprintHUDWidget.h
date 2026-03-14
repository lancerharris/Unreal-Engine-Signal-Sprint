#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SignalSprintHUDWidget.generated.h"

struct FGameStatePayload;
class ASignalSprintGameState;
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

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StrikesText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StateText;

	ASignalSprintGameState* GameState = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="HUD")
	int32 FinalScore = -1;

	void HandleGameStateChanged(const FGameStatePayload&);

	void UpdateFinalScore();
};