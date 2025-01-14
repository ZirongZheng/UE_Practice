// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TimerManager.h"
#include "UI/UIManager.h"
#include "AFPSDemoPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FPSDEMO_API AAFPSDemoPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void InitPlayerState();

	void AddScore(float Points);

	void GetDamage(float Damage);

	void HitTarget();

	bool TryUseAmmo();

	void FillAmmo();
private:
	UPROPERTY()
	float CurHealth;

	UPROPERTY()
	float MaxHealth;

	UPROPERTY()
	int CurAmmo;

	UPROPERTY()
	int MaxAmmo;

	float ReloadTime = 2.0;

	FTimerHandle ReloadHandle;
};
