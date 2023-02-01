// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketExplosion.h"
#include <PhysicsEngine/RadialForceComponent.h>
#include <Components/SphereComponent.h>
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
	radialForceComp->Radius = 500.f;
	radialForceComp->ImpulseStrength = 40000.f;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	sphereComp->SetupAttachment(RootComponent);
	sphereComp->SetSphereRadius(500.f);
	sphereComp->SetCollisionProfileName(TEXT("ExplosionPreset"));

}	

// Called when the game starts or when spawned
void ARocketExplosion::BeginPlay()
{
	Super::BeginPlay();

	radialForceComp->FireImpulse();
	GetWorld()->GetTimerManager().SetTimer(destroyTimer, this, &ARocketExplosion::SelfDestroy, 0.5f, false);
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARocketExplosion::OnOverlap);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), rocketExplosionFX, GetActorTransform());
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
}

void ARocketExplosion::SelfDestroy()
{
	Destroy();
}

