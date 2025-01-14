// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "AFPSDemoPlayerState.h"
#include "TargetCube.h"
#include "UI/LoginWidget.h"
#include "UI/UIManager.h"
#include <Kismet/GameplayStatics.h>
#include "FPSDemoGameMode.generated.h"




UCLASS(minimalapi)
class AFPSDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings");
	int32 m_BonusCnt = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
	float m_GameTimeLimit = 60.0f;
private:
	FTimerHandle m_GameTimeHandler;
	float LoadingProgress;
	FTimerHandle LoadingTimerHandle;
public:
	AFPSDemoGameMode();
	void BeginPlay() override;
	void InitializeGame();
	void InitializeUI();
	void MarkBonusTargets();
	void StartGame();
	void LoadGame();
	void UpdateLoading();
	void ResumeGame();
	void EndGame();
};



