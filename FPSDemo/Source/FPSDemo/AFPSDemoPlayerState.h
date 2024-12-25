// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AFPSDemoPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FPSDEMO_API AAFPSDemoPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void AddScore(float Points);
};
