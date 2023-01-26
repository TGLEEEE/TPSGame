// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketExplosion.h"
#include <PhysicsEngine/RadialForceComponent.h>
#include <Components/SphereComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include "Enemy.h"
#include "EnemyFSM.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ARocketExplosion::ARocketExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	radialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force Component"));
	SetRootComponent(radialForceComp);
	radialForceComp->Radius = 600.f;
	radialForceComp->ImpulseStrength = 40000.f;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	sphereComp->SetupAttachment(RootComponent);
	sphereComp->SetSphereRadius(600.f);

	particleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Component"));
	particleComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UParticleSystem>tempExplosionFX(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Weapon/MilitaryWeapSilver/FX/P_RocketLauncher_Explosion_01.P_RocketLauncher_Explosion_01'"));
	if (tempExplosionFX.Succeeded())
	{
		particleComp->SetTemplate(tempExplosionFX.Object);
	}
}	

// Called when the game starts or when spawned
void ARocketExplosion::BeginPlay()
{
	Super::BeginPlay();

	radialForceComp->FireImpulse();
	GetWorld()->GetTimerManager().SetTimer(destroyTimer, this, &ARocketExplosion::SelfDestroy, 3.f, false);
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARocketExplosion::OnOverlap);
}

// Called every frame
void ARocketExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARocketExplosion::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy*	enemy = Cast<AEnemy>(OtherActor);
	if (enemy)
	{
		UEnemyFSM* fsm = Cast<UEnemyFSM>(enemy->fsm);
		if (fsm)
		{
			fsm->OnDamageProcess(10);
		}
	}
	sphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARocketExplosion::SelfDestroy()
{
	Destroy();
}

