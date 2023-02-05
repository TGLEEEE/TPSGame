// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowTrap.h"
#include <Components/BoxComponent.h>
#include "EnemyFSM.h"
#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASlowTrap::ASlowTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

	boxComp->SetCollisionProfileName(TEXT("TrapPreset"));

}

// Called when the game starts or when spawned
void ASlowTrap::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ASlowTrap::InSlowTrap);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &ASlowTrap::OutSlowTrap);
}

// Called every frame
void ASlowTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

 void ASlowTrap::InSlowTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
 {
	// UE_LOG(LogTemp, Warning, TEXT("dasss"));

 	AEnemy* enemy = Cast<AEnemy>(OtherActor);
 	if (enemy)
 	{
		enemy->GetCharacterMovement()->MaxWalkSpeed = 100;
		
		//enemy에잇는 canMove변수를 False로만든다
		//UEnemyFSM* FSMEnemy = Cast<UEnemyFSM>(enemy->fsm);
		//if (FSMEnemy)
		//{
		//}
 	}
 
 }

void ASlowTrap::OutSlowTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	if (enemy)
	{
		enemy->GetCharacterMovement()->MaxWalkSpeed = 600;
	}
}


