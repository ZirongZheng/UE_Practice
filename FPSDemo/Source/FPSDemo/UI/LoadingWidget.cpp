// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingWidget.h"

void ULoadingWidget::UpdateProgress(float Progress)
{
	if (m_LoadingProgressBar != nullptr)
	{
		m_LoadingProgressBar->SetPercent(Progress);
	}
}
