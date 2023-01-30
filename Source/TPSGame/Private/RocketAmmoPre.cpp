// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketAmmoPre.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ARocketAmmoPre::ARocketAmmoPre()
{
	projectileComp->InitialSpeed = 600.f;
	projectileComp->MaxSpeed = 600.f;
	projectileComp->ProjectileGravityScale = 1.0f;
	projectileComp->SetVelocityInLocalSpace(FVector(1.f, 0, 0.4f));

	particleComp->SetVisibility(false);

}

void ARocketAmmoPre::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(fireTimer, this, &ARocketAmmoPre::SpawnFireAmmo, 0.5f);
}

void ARocketAmmoPre::SpawnFireAmmo()
{
	GetWorld()->SpawnActor<ARocketAmmo>(fireAmmoFactory, GetActorLocation(), GetActorRotation());
	Destroy();
}
