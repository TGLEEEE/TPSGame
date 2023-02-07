// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeExplosion.h"
#include <PhysicsEngine/RadialForceComponent.h>
#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>
#include "EnemyFSM.h"
#include "Enemy.h"
#include "EngineUtils.h"

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
	sphereComp->SetCollisionProfileName(TEXT("ExplosionPreset"));

}

// Called when the game starts or when spawned
void AGrenadeExplosion::BeginPlay()
{
	Super::BeginPlay();

	radialForceComp->FireImpulse();
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AGrenadeExplosion::OnOverlap);
	GetWorldTimerManager().SetTimer(destroyHandle, this, &AGrenadeExplosion::SelfDestroy, 0.5f);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), grenadeExplosionFX, GetActorTransform());
}

// Called every frame
void AGrenadeExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGrenadeExplosion::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	if (enemy)
	{
		UEnemyFSM* fsm = Cast<UEnemyFSM>(enemy->fsm);
		if (fsm)
		{
			fsm->OnDamageProcess(5);
		}
		for (AMyPlayer* player : TActorRange<AMyPlayer>(GetWorld()))
		{
			if (player)
			{
				player->SpawnBloodEffect(enemy->GetActorLocation(), enemy->GetActorRotation());
				player->CrossHit();
			}
		}
	}
}

void AGrenadeExplosion::SelfDestroy()
{
	Destroy();
}
