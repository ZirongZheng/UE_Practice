// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

void UHUDWidget::UpdateHealth(float percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(percent);
	}
}

void UHUDWidget::UpdateAmmo(int32 InCurrentAmmo, int32 InMaxAmmo)
{
	if (AmmoText)
	{
		AmmoText->SetText(FText::Format(NSLOCTEXT("HUD", "AmmoText", "{0}/{1}"), FText::AsNumber(InCurrentAmmo), FText::AsNumber(InMaxAmmo)));
	}
}

void UHUDWidget::UpdateReload()
{
	if (AmmoText)
	{
		AmmoText->SetText(FText::FromString("Reloading"));
	}
}

void UHUDWidget::UpdateScore(float InScore)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::AsNumber(InScore));
	}
}

void UHUDWidget::UpdateCrosshair(bool bInHitTarget)
{
	if (CrosshairImage)
	{
		if (bInHitTarget)
		{
			if (!GetWorld()) return;

			GetWorld()->GetTimerManager().SetTimer(
				CrosshairResetTimerHandle,
				this,
				&UHUDWidget::ResetCrosshair,
				CrosshairResetDelay,
				false
			);
		}

		FLinearColor NewColor = FLinearColor::Red;
		CrosshairImage->SetColorAndOpacity(NewColor);
	}
}

void UHUDWidget::ResetCrosshair()
{
	if (CrosshairImage)
	{
		FLinearColor NewColor = FLinearColor::White;
		CrosshairImage->SetColorAndOpacity(NewColor);
	}
}
