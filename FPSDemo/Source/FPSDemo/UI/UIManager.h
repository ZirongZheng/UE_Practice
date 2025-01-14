// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoginWidget.h"
#include "LoadingWidget.h"
#include "UIManager.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EUIType : uint8
{
	Login UMETA(DisplayName = "Login"),
	Loading UMETA(DisplayName = "Loading"),
	MainMenu UMETA(DisplayName = "MainMenu"),
	HUD UMETA(DisplayName = "HUD"),
};


UCLASS()
class FPSDEMO_API UUIManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // 管理UI的函数
    
    void ShowWidget(EUIType UIType);
    void HideWidget(EUIType UIType);
    UUserWidget* GetWidget(EUIType UIType);
    UUserWidget* CreateUIWidget(EUIType UIType);

private:
    // 存储所有UI的映射
    TMap<EUIType, UUserWidget*> m_UIInstances;
    TMap<EUIType, TSubclassOf<UUserWidget>> m_UIPaths;
};
