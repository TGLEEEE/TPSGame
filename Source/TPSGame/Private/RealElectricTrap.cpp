// Fill out your copyright notice in the Description page of Project Settings.


#include "RealElectricTrap.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ElectricTrap.h"
#include "Enemy.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ARealElectricTrap::ARealElectricTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));
	arrow->SetupAttachment(RootComponent);

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	boxComp->SetCollisionProfileName(TEXT("TrapPreset"));
	boxComp->SetBoxExtent(FVector(240, 380, 10));



}

// Called when the game starts or when spawned
void ARealElectricTrap::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ARealElectricTrap::InRealElectricTrap);

	
}

// Called every frame
void ARealElectricTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
	if (currentTime >= shockTime)
	{
		//UE_LOG(LogTemp, Warning, TEXT("elc"));

		GetWorld()->SpawnActor<AElectricTrap>(electricFactory, GetActorLocation(), GetActorRotation());


		currentTime = 0;

	}
}

void ARealElectricTrap::InRealElectricTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	enemy = Cast<AEnemy>(OtherActor);
	if (nullptr != enemy)
	{

		UE_LOG(LogTemp, Warning, TEXT("ssshock"));
		enemy->GetCharacterMovement()->MaxWalkSpeed = 0;

		GetWorldTimerManager().SetTimer(moveHandle, FTimerDelegate::CreateLambda([&]()
			{
				enemy->GetCharacterMovement()->MaxWalkSpeed = 600;
			}), 1.5f, false);

		/*
		UEnemyFSM* FSMEnemy = Cast<UEnemyFSM>(enemy->fsm);
		if (FSMEnemy)
		{
			//FSMEnemy->canMove = false;
		}
		*/
	}
}

