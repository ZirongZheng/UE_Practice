// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

void UUIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    m_UIPaths.Add(EUIType::Login, LoadClass<UUserWidget>(nullptr, TEXT("/Game/FirstPerson/Blueprints/UI/BP_LoginWidget.BP_LoginWidget_C")));
    m_UIPaths.Add(EUIType::Loading, LoadClass<UUserWidget>(nullptr, TEXT("/Game/FirstPerson/Blueprints/UI/BP_LoadingWidget.BP_LoadingWidget_C")));
    m_UIPaths.Add(EUIType::HUD, LoadClass<UUserWidget>(nullptr, TEXT("/Game/FirstPerson/Blueprints/UI/BP_HUDWidget.BP_HUDWidget_C")));
}

void UUIManager::Deinitialize()
{
    Super::Deinitialize();

    // 清理所有UI实例
    for (auto& Pair : m_UIInstances)
    {
        if (Pair.Value)
        {
            Pair.Value->RemoveFromViewport();
            Pair.Value->ConditionalBeginDestroy();
        }
    }
    m_UIInstances.Empty();
}

void UUIManager::ShowWidget(EUIType UIType)
{
    if (m_UIInstances.Contains(UIType))
    {
        m_UIInstances[UIType]->AddToViewport();
    }
    else
    {
        UUserWidget* uiw = CreateUIWidget(UIType);
        if (uiw != nullptr)
        {
            uiw->AddToViewport();
        }
    }
}

void UUIManager::HideWidget(EUIType UIType)
{
    if (m_UIInstances.Contains(UIType))
    {
        m_UIInstances[UIType]->RemoveFromViewport();
    }
}

UUserWidget* UUIManager::GetWidget(EUIType UIType)
{
    if (m_UIInstances.Contains(UIType))
    {
        return m_UIInstances[UIType];
    }
    return nullptr;
}

UUserWidget* UUIManager::CreateUIWidget(EUIType UIType)
{
    if (m_UIPaths.Contains(UIType))
    {
        UClass* WidgetClass = m_UIPaths[UIType];
        if (WidgetClass == nullptr)
        {
            return nullptr;
        }
        UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        if (NewWidget != nullptr)
        {
            m_UIInstances.Add(UIType, NewWidget);
        }
        return NewWidget;
    }
    return nullptr;
}


