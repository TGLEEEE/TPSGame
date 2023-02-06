// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricTrap.h"

#include "Enemy.h"
#include "EnemyFSM.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AElectricTrap::AElectricTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElectricTrap::BeginPlay()
{
	Super::BeginPlay();
	

	//sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	//SetRootComponent(sphereComp);
	//sphereComp->SetCollisionProfileName(TEXT("TrapPreset"));

}

// Called every frame
void AElectricTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AElectricTrap::InElectricTrap);
	//boxComp->OnComponentEndOverlap.AddDynamic(this, &AElectricTrap::OutElectricTrap);

	
}

	

void AElectricTrap::InElectricTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	if (nullptr != enemy)
	{
		UEnemyFSM* FSMEnemy = Cast<UEnemyFSM>(enemy->fsm);
		if (FSMEnemy)
		{
			FSMEnemy->canMove = false;
		}
	}
}


//}
//}

//void AElectricTrap::OutElectricTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{

//}

