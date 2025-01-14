// Fill out your copyright notice in the Description page of Project Settings.


#include "AFPSDemoPlayerState.h"
#include "UI/HUDWidget.h"

#define MAX_AMMO 20
#define MAX_HEALTH 10

void AAFPSDemoPlayerState::InitPlayerState()
{
	SetScore(0);

	MaxAmmo = MAX_AMMO;
	MaxHealth = MAX_HEALTH;
	CurAmmo = MaxAmmo;
	CurHealth = MaxHealth;

	UUIManager* pUIManager = GetGameInstance()->GetSubsystem<UUIManager>();
	if (pUIManager == nullptr)
	{
		return;
	}

	UHUDWidget* widget = Cast<UHUDWidget>(pUIManager->GetWidget(EUIType::HUD));
	if (widget == nullptr)
	{
		return;
	}

	widget->UpdateScore(GetScore());
	widget->UpdateAmmo(CurAmmo, MaxAmmo);
	widget->UpdateHealth(CurHealth / MaxHealth);
}

void AAFPSDemoPlayerState::AddScore(float Points)
{
	SetScore(GetScore() + Points);

	UUIManager* pUIManager = GetGameInstance()->GetSubsystem<UUIManager>();
	if (pUIManager == nullptr)
	{
		return;
	}

	UHUDWidget* widget = Cast<UHUDWidget>(pUIManager->GetWidget(EUIType::HUD));
	if (widget == nullptr)
	{
		return;
	}
	widget->UpdateScore(GetScore());

	UE_LOG(LogTemp, Log, TEXT("Player %s new score: %f"), *GetPlayerName(), GetScore());
}

void AAFPSDemoPlayerState::GetDamage(float Damage)
{
	CurHealth -= Damage;
	if (CurHealth <= 0)
	{
		//TODO: ½ÇÉ«ËÀÍö
	}
	else
	{
		UUIManager * pUIManager = GetGameInstance()->GetSubsystem<UUIManager>();
		if (pUIManager == nullptr)
		{
			return;
		}

		UHUDWidget* widget = Cast<UHUDWidget>(pUIManager->GetWidget(EUIType::HUD));
		if (widget == nullptr)
		{
			return;
		}
		widget->UpdateHealth(CurHealth / MaxHealth);
	}
}

void AAFPSDemoPlayerState::HitTarget()
{
	UUIManager* pUIManager = GetGameInstance()->GetSubsystem<UUIManager>();
	if (pUIManager == nullptr)
	{
		return;
	}

	UHUDWidget* widget = Cast<UHUDWidget>(pUIManager->GetWidget(EUIType::HUD));
	if (widget == nullptr)
	{
		return;
	}
	widget->UpdateCrosshair(true);
}

bool AAFPSDemoPlayerState::TryUseAmmo()
{
	if (CurAmmo <= 0)
	{
		return false;
	}
	CurAmmo--;
	UUIManager* pUIManager = GetGameInstance()->GetSubsystem<UUIManager>();
	if (pUIManager == nullptr)
	{
		return false;
	}

	UHUDWidget* widget = Cast<UHUDWidget>(pUIManager->GetWidget(EUIType::HUD));
	if (widget == nullptr)
	{
		return false;
	}

	if (CurAmmo == 0)
	{
		GetWorldTimerManager().ClearTimer(ReloadHandle);

		FTimerManager& timeManager = GetWorldTimerManager();
		timeManager.SetTimer(ReloadHandle, this, &AAFPSDemoPlayerState::FillAmmo, ReloadTime, false);
		widget->UpdateReload();
	}
	else
	{
		widget->UpdateAmmo(CurAmmo, MaxAmmo);
	}
	return true;
}

void AAFPSDemoPlayerState::FillAmmo()
{
	CurAmmo = MaxAmmo;

	UUIManager* pUIManager = GetGameInstance()->GetSubsystem<UUIManager>();
	if (pUIManager == nullptr)
	{
		return;
	}

	UHUDWidget* widget = Cast<UHUDWidget>(pUIManager->GetWidget(EUIType::HUD));
	if (widget == nullptr)
	{
		return;
	}

	widget->UpdateAmmo(CurAmmo, MaxAmmo);
}
