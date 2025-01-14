// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSDemoProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AFPSDemoProjectile::AFPSDemoProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPSDemoProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AFPSDemoProjectile::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);


	if (AController* OwnerController = Cast<AController>(NewOwner))
	{
		OwningPlayerState = Cast<AAFPSDemoPlayerState>(OwnerController->GetPlayerState<APlayerState>());
	}
	else if (APawn* OwnerPawn = Cast<APawn>(NewOwner))
	{
		OwningPlayerState = Cast<AAFPSDemoPlayerState>(OwnerPawn->GetPlayerState());
	}
}


void AFPSDemoProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) 
			&& OtherComp->IsSimulatingPhysics() && (OwningPlayerState != nullptr))
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		ATargetCube* pCube = Cast<ATargetCube>(OtherActor);
		if (pCube != nullptr)
		{
			OwningPlayerState->AddScore(pCube->GetBonusPoint());
			OwningPlayerState->HitTarget();
			pCube->HandleHit();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("TargetCube Not Exist"));
		}

		Destroy();
	}
}