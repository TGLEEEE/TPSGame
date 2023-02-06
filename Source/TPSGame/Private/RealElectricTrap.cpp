// Fill out your copyright notice in the Description page of Project Settings.


#include "RealElectricTrap.h"

#include "ElectricTrap.h"
#include "Components/ArrowComponent.h"

// Sets default values
ARealElectricTrap::ARealElectricTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("arrow"));
	arrow->SetupAttachment(RootComponent);



}

// Called when the game starts or when spawned
void ARealElectricTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARealElectricTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentTime += DeltaTime;
	if (currentTime >= shockTime)
	{
		UE_LOG(LogTemp, Warning, TEXT("elc"));

		GetWorld()->SpawnActor<AElectricTrap>(electricFactory, GetActorLocation(), GetActorRotation());

		currentTime = 0;

	}
}

