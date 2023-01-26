// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeExplosion.h"
#include <PhysicsEngine/RadialForceComponent.h>
#include <Components/SphereComponent.h>
#include <Particles/ParticleSystemComponent.h>

// Sets default values
AGrenadeExplosion::AGrenadeExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	radialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force Component"));
	SetRootComponent(radialForceComp);
	radialForceComp->Radius = 300.f;
	radialForceComp->ImpulseStrength = 10000.f;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	sphereComp->SetupAttachment(RootComponent);
	sphereComp->SetSphereRadius(300.f);

	particleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Component"));
	particleComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UParticleSystem>tempExplosionFX(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Weapon/MilitaryWeapSilver/FX/P_Grenade_Explosion_01.P_Grenade_Explosion_01'"));
	if (tempExplosionFX.Succeeded())
	{
		particleComp->SetTemplate(tempExplosionFX.Object);
	}
}

// Called when the game starts or when spawned
void AGrenadeExplosion::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle destroyHandle;

}

// Called every frame
void AGrenadeExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGrenadeExplosion::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AGrenadeExplosion::SelfDestroy()
{
	Destroy();
}
