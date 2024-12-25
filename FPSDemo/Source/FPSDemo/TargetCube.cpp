// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetCube.h"


// Sets default values
ATargetCube::ATargetCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	m_bIsHit = false;
	m_bIsBonusTarget = false;
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	m_Mesh->SetCollisionProfileName(TEXT("BlockAll"));
	m_Mesh->SetSimulatePhysics(true);
	if (!m_DefaultMaterial)
	{
		m_DefaultMaterial = m_Mesh->GetMaterial(0);
	}
	else
	{
		m_Mesh->SetMaterial(0, m_DefaultMaterial);
	}
	
	RootComponent = m_Mesh;
}

// Called when the game starts or when spawned
void ATargetCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATargetCube::HandleHit()
{
	if (!m_bIsHit)
	{
		SetActorScale3D(GetActorScale3D() * m_Scale);
		m_bIsHit = true;
	}
	else
	{
		Destroy();
	}
}

float ATargetCube::GetBonusPoint()
{
	return m_bIsBonusTarget ? m_Points * 2 : m_Points;
}

void ATargetCube::SetTargetType(bool isBounus)
{
	m_bIsBonusTarget = isBounus;
	if (m_bIsBonusTarget)
	{
		m_Mesh->SetMaterial(0, m_BonusMaterial);
	}
}

