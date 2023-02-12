// Fill out your copyright notice in the Description page of Project Settings.


#include "StartTrigger.h"
#include <Components/BoxComponent.h>
#include "MyPlayer.h"
#include <Blueprint/UserWidget.h>
#include "WorldWarGameMode.h"

// Sets default values
AStartTrigger::AStartTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	boxComp->SetBoxExtent(FVector(50.f, 500.f, 50.f));
}

// Called when the game starts or when spawned
void AStartTrigger::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AStartTrigger::OnOverlap);
	gm = Cast<AWorldWarGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AStartTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (gm->bCanSpawnZombie && !bDoOnce)
	{
		FTimerHandle tempHandle;
		GetWorldTimerManager().SetTimer(tempHandle, FTimerDelegate::CreateLambda([&]()
		{
			gm->CountdownTimer(180);
		}), 2, false);
		bDoOnce = true;
	}
}

void AStartTrigger::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	player = Cast<AMyPlayer>(OtherActor);
	if (player && !gm->bIsStarted)
	{
		player->warningTextUI->AddToViewport();
		gm->bIsStarted = true;
		gm->CountdownTimer(30);
		gm->stage++;
	}
}

