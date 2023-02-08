// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricTrap.h"

#include "Enemy.h"
#include "EnemyFSM.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AElectricTrap::AElectricTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SetRootComponent(sphereComp);
	sphereComp->SetCollisionProfileName(TEXT("TrapPreset"));
	sphereComp->SetSphereRadius(250.0f);

	particleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("particleComp"));
	particleComp->SetupAttachment(RootComponent);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AElectricTrap::BeginPlay()
{
	Super::BeginPlay();

	//sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AElectricTrap::InElectricTrap);


	
}

// Called every frame
void AElectricTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
	if (currentTime > shockTime)
	{
		Destroy();

	}
	
}

	
/*
void AElectricTrap::InElectricTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	enemy = Cast<AEnemy>(OtherActor);
	if (nullptr != enemy)
	{
		enemy->GetCharacterMovement()->MaxWalkSpeed = 0;

		GetWorldTimerManager().SetTimer(moveHandle, FTimerDelegate::CreateLambda([&]()
		{
			enemy->GetCharacterMovement()->MaxWalkSpeed = 600;
		}),1.5f , false);
		/*
		UEnemyFSM* FSMEnemy = Cast<UEnemyFSM>(enemy->fsm);
		if (FSMEnemy)
		{
			//FSMEnemy->canMove = false;
		}
		*/



//}
//}

//void AElectricTrap::OutElectricTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{

//}

