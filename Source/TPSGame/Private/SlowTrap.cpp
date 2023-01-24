// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowTrap.h"
#include <Components/BoxComponent.h>
#include "EnemyFSM.h"

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


}

// Called when the game starts or when spawned
void ASlowTrap::BeginPlay()
{
	Super::BeginPlay();
	
//	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ASlowTrap::InSlowTrap);
}

// Called every frame
void ASlowTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// void ASlowTrap::InSlowTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	UEnemyFSM* enemy = Cast<UEnemyFSM>(OtherActor);
// 	if (enemy)
// 	{
// 		//플레이어에잇는 canfire변수를 False로만든다
// 		enemy->canMove = false;
// 	}
// 
// }

