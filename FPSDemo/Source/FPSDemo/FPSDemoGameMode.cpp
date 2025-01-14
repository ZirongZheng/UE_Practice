// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSDemoGameMode.h"
#include "FPSDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

void AFPSDemoGameMode::BeginPlay()
{
    Super::BeginPlay();

    InitializeUI();
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

void AFPSDemoGameMode::InitializeUI()
{
    UUIManager* UIManager = GetGameInstance()->GetSubsystem<UUIManager>();
    if (UIManager == nullptr)
    {
        UE_LOG(LogTemp, Log, TEXT("UIManager Is null"));
        return;
    }

    UIManager->ShowWidget(EUIType::Login);

    UUserWidget* LoginWidget = UIManager->GetWidget(EUIType::Login);
    if (LoginWidget == nullptr)
    {
        UE_LOG(LogTemp, Log, TEXT("LoginWidget is null"));
        return;
    }

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(LoginWidget->TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PlayerController->SetInputMode(InputMode);

        PlayerController->bShowMouseCursor = true;
    }
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
    ResumeGame();

    UUIManager* UIManager = GetGameInstance()->GetSubsystem<UUIManager>();
    if (UIManager == nullptr)
    {
        UE_LOG(LogTemp, Log, TEXT("UIManager Is null"));
        return;
    }
    UIManager->ShowWidget(EUIType::HUD);

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController == nullptr)
    {
        return;
    }

    AAFPSDemoPlayerState* playerState = Cast<AAFPSDemoPlayerState>(PlayerController->GetPlayerState<APlayerState>());
    if (playerState != nullptr)
    {
        playerState->InitPlayerState();
    }
}

void AFPSDemoGameMode::LoadGame()
{
    UUIManager* uiManager = GetGameInstance()->GetSubsystem<UUIManager>();
    if (uiManager == nullptr)
    {
        return;
    }
    uiManager->ShowWidget(EUIType::Loading);

    LoadingProgress = 0.0f;
    // 启动计时器
    GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle, this, &AFPSDemoGameMode::UpdateLoading, 0.1f, true);
}

void AFPSDemoGameMode::UpdateLoading()
{
    LoadingProgress += 0.05f;

    UUIManager* uiManager = GetGameInstance()->GetSubsystem<UUIManager>();
    if (uiManager == nullptr)
    {
        return;
    }
    ULoadingWidget* loadingUIW =  Cast<ULoadingWidget>(uiManager->GetWidget(EUIType::Loading));
    if (loadingUIW != nullptr)
    {
        loadingUIW->UpdateProgress(LoadingProgress);
    }

    if (LoadingProgress >= 1.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(LoadingTimerHandle);

        uiManager->HideWidget(EUIType::Loading);

        // 加载完成后，恢复游戏
        InitializeGame();
    }
}



void AFPSDemoGameMode::ResumeGame()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);

        PlayerController->bShowMouseCursor = false;
    
        UGameplayStatics::SetGamePaused(GetWorld(), false);

    }
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
