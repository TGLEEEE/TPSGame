// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketAmmo.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "RocketExplosion.h"
#include <Particles/ParticleSystemComponent.h>

// Sets default values
ARocketAmmo::ARocketAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	sphereComp=CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(16.f);
	sphereComp->SetCollisionProfileName(TEXT("BlockAll"));

	MeshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skeletal Mesh"));
	MeshComp->SetupAttachment(sphereComp);
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshTemp(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Weapon/MilitaryWeapSilver/Weapons/RocketLauncherA_Ammo.RocketLauncherA_Ammo'"));
	if (MeshTemp.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshTemp.Object);
	}

	projectileComp=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	projectileComp->InitialSpeed = 1200.f;
	projectileComp->MaxSpeed = 1200.f;
	projectileComp->ProjectileGravityScale = 0.f;
	projectileComp->bShouldBounce = false;
	projectileComp->SetUpdatedComponent(sphereComp);

	particleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Comp"));
	particleComp->SetupAttachment(MeshComp);
	ConstructorHelpers::FObjectFinder<UParticleSystem>tempFX(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Weapon/MilitaryWeapSilver/FX/P_RocketLauncher_Trail_01.P_RocketLauncher_Trail_01'"));
	if (tempFX.Succeeded())
	{
		particleComp->SetTemplate(tempFX.Object);
	}

}

// Called when the game starts or when spawned
void ARocketAmmo::BeginPlay()
{
	Super::BeginPlay();
	
	sphereComp->OnComponentHit.AddDynamic(this, &ARocketAmmo::OnHit);
}

// Called every frame
void ARocketAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARocketAmmo::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
//	UE_LOG(LogTemp, Warning, TEXT("boooooom!!"));
	GetWorld()->SpawnActor<ARocketExplosion>(explosion, GetActorLocation(), FRotator::ZeroRotator);
	Destroy();
}

