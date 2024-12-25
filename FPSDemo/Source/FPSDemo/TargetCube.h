// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetCube.generated.h"

UCLASS()
class FPSDEMO_API ATargetCube : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ATargetCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	float m_Points = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	bool m_bIsBonusTarget = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	UMaterialInterface* m_DefaultMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	UMaterialInterface* m_BonusMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	float m_Scale = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	bool m_bIsHit = false;

	void HandleHit();

	float GetBonusPoint();

	void SetTargetType(bool isBonus);
};
