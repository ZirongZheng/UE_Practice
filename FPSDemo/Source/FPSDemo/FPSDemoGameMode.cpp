// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSDemoGameMode.h"
#include "FPSDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

void AFPSDemoGameMode::BeginPlay()
{
    Super::BeginPlay();

    InitializeGame();
}

AFPSDemoGameMode::AFPSDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerStateClass = AAFPSDemoPlayerState::StaticClass();
}

void AFPSDemoGameMode::InitializeGame()
{
    UE_LOG(LogTemp, Log, TEXT("Game Initialized"));
    MarkBonusTargets();
    StartGame();
}

void AFPSDemoGameMode::MarkBonusTargets()
{
	TArray<AActor*> FoundCubes;
	UGameplayStatics::GetAllActorsOfClass(this, ATargetCube::StaticClass(), FoundCubes);

    if (FoundCubes.Num() > 0)
    {
        for (int32 i = 0; i < m_BonusCnt; ++i)
        {
            int32 RandomIndex = FMath::RandRange(0, FoundCubes.Num() - 1);
            ATargetCube* TargetCube = Cast<ATargetCube>(FoundCubes[RandomIndex]);
            if (TargetCube && !TargetCube->m_bIsBonusTarget)
            {
                TargetCube->SetTargetType(true);
            }
        }
    }
}

void AFPSDemoGameMode::StartGame()
{
    FTimerManager& timeManager = GetWorldTimerManager();
    timeManager.SetTimer(m_GameTimeHandler, this, &AFPSDemoGameMode::EndGame, m_GameTimeLimit, false);
}

void AFPSDemoGameMode::EndGame()
{
    GetWorldTimerManager().ClearTimer(m_GameTimeHandler);

    AGameStateBase* gameStateBase = GetGameState<AGameStateBase>();
    int32 TotalScore = 0;
    if (gameStateBase != nullptr)
    {
        TArray<APlayerState*> PlayerStates = gameStateBase->PlayerArray;

        for (APlayerState* PlayerState : PlayerStates)
        {
            if (AAFPSDemoPlayerState* FPSPlayerState = Cast<AAFPSDemoPlayerState>(PlayerState))
            {
                UE_LOG(LogTemp, Log, TEXT("Player %s scored: %f"), *FPSPlayerState->GetPlayerName(), FPSPlayerState->GetScore());
                TotalScore += FPSPlayerState->GetScore();
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Total Score: %d"), TotalScore);
}
