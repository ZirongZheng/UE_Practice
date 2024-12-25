// Fill out your copyright notice in the Description page of Project Settings.


#include "AFPSDemoPlayerState.h"

void AAFPSDemoPlayerState::AddScore(float Points)
{
	SetScore(GetScore() + Points);
	UE_LOG(LogTemp, Log, TEXT("Player %s new score: %f"), *GetPlayerName(), GetScore());
}
