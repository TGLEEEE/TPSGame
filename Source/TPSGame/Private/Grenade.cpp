// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

#include "GrenadeExplosion.h"
#include "Components/SphereComponent.h"
#include "GrenadeExplosion.h"

// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	grenadeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(grenadeComp);
	//grenadeComp->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempGrenade(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Weapon/MilitaryWeapSilver/Weapons/GrenadeLauncherA_Ammo.GrenadeLauncherA_Ammo'"));
	if (tempGrenade.Succeeded())
	{
		grenadeComp->SetStaticMesh(tempGrenade.Object);
	}
	grenadeComp->SetRelativeScale3D(FVector(3.f));
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle exTimerhandle;
	GetWorldTimerManager().SetTimer(exTimerhandle, this, &AGrenade::SelfExplosion, 3.f, false);
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenade::SelfExplosion()
{
	GetWorld()->SpawnActor<AGrenadeExplosion>(explosion, GetActorLocation(), FRotator::ZeroRotator);
	Destroy();
}

