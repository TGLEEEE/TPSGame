// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(10.0f));


	boxComp->SetCollisionProfileName(TEXT("TrapPreset"));
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AWall::InWall);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &AWall::OutWall);
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::InWall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	if (enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("dasd"));
		currentTime += GetWorld()->DeltaTimeSeconds;
		FVector P0 = enemy->GetActorLocation();
		FVector vt = FVector(0,0,1) * 200 * GetWorld()->DeltaTimeSeconds;
		FVector P = P0 + vt;


	}
	
}

void AWall::OutWall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}

