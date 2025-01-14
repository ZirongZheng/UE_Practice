// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "LoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSDEMO_API ULoadingWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, Category = "Loading")
	void UpdateProgress(float Progress);
	
private:


	UPROPERTY(meta = (BindWidget))
	class UProgressBar* m_LoadingProgressBar;
};
