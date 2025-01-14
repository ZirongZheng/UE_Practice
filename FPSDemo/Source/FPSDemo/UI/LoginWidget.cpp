// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginWidget.h"
#include "UIManager.h"
#include "FPSDemo/FPSDemoGameMode.h"


void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (m_ConfirmButton == nullptr)
	{
		return;
	}

	m_ConfirmButton->OnClicked.AddDynamic(this, &ULoginWidget::OnConfirmButtonClicked);

	UE_LOG(LogTemp, Warning, TEXT("LoginWidget NativeConstruct"));
}

void ULoginWidget::OnConfirmButtonClicked()
{
	if (m_UsernameTextBox == nullptr || m_PasswordTextBox == nullptr) 
	{
		return;
	}

	FString Username = m_UsernameTextBox->GetText().ToString();
	FString Password = m_PasswordTextBox->GetText().ToString();

	UE_LOG(LogTemp, Warning, TEXT("Username: %s"), *Username);
	UE_LOG(LogTemp, Warning, TEXT("Password: %s"), *Password);

	AFPSDemoGameMode* gameMode = Cast<AFPSDemoGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode != nullptr)
	{
		gameMode->LoadGame();
	}

	UUIManager* pUIManager = GetGameInstance()->GetSubsystem<UUIManager>();
	if (pUIManager)
	{
		pUIManager->HideWidget(EUIType::Login);
	}
}


