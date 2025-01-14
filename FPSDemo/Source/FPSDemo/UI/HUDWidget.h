// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSDEMO_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateHealth(float percent);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateAmmo(int32 InCurrentAmmo, int32 InMaxAmmo);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateReload();

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateScore(float InScore);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateCrosshair(bool bInHitTarget);
	
	UFUNCTION()
    void ResetCrosshair();
private:
    /** Reference to the health progress bar widget */
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthProgressBar;

    /** Reference to the ammo text widget */
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* AmmoText;

    /** Reference to the score text widget */
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ScoreText;

    /** Reference to the crosshair image widget */
    UPROPERTY(meta = (BindWidget))
    class UImage* CrosshairImage;

    float CrosshairResetDelay = 0.5f;
    FTimerHandle CrosshairResetTimerHandle;
};
