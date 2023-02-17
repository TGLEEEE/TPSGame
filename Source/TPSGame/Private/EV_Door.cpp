// Fill out your copyright notice in the Description page of Project Settings.


#include "EV_Door.h"
#include <Components/BoxComponent.h>
#include "MyPlayer.h"

// Sets default values
AEV_Door::AEV_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
 	boxComp->SetRelativeScale3D(FVector(2.f, 3.5f, 2.f));

	doorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Door"));
	doorLeft->SetupAttachment(boxComp);
	doorLeft->SetRelativeScale3D(FVector(0.25f, 0.75f, 2.5f));
	doorLeft->SetRelativeLocation(FVector(-80.f, 115.f, 55.f));

	doorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Door"));
	doorRight->SetupAttachment(boxComp);
	doorRight->SetRelativeScale3D(FVector(0.25f, 0.75f, 2.5f));
	doorRight->SetRelativeLocation(FVector(-70.f, 40.f, 55.f));

	ConstructorHelpers::FObjectFinder<UStaticMesh>tempBoxMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempBoxMesh.Succeeded())
	{
		doorLeft->SetStaticMesh(tempBoxMesh.Object);
		doorRight->SetStaticMesh(tempBoxMesh.Object);
	}

}

// Called when the game starts or when spawned
void AEV_Door::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEV_Door::OnOverlap);
	boxComp->OnComponentEndOverlap.AddDynamic(this, &AEV_Door::EndOverlap);

	startLocLeft = doorLeft->GetRelativeLocation();
	endLocLeft = startLocLeft + FVector(0, -80.f, 0);
	startLocRight = doorRight->GetRelativeLocation();
	endLocRight = startLocRight + FVector(0, -80.f, 0);
}

// Called every frame
void AEV_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bDoOpen)
	{
		moveLeftDoor(startLocLeft, endLocLeft);
		if (bOpenRightDelay)
		{
			moveRightDoor(startLocRight, endLocRight);
		}
		if (doorRight->GetRelativeLocation() == endLocRight)
		{
			if (!bDoClose)
			{
				bDoOpen = false;
				bDoClose = true;
				timeL = 0;
				timeR = 0;
			}
		}
	}
	if (bDoClose)
	{
		moveLeftDoor(endLocLeft, startLocLeft);
		moveRightDoor(endLocRight, startLocRight);
		if (doorRight->GetRelativeLocation() == startLocRight)
		{
			bDoClose = false;
			bOpenRightDelay = false;
			bDoOnce = false;
			timeL = 0;
			timeR = 0;
		}
	}
}

void AEV_Door::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
	if (player)
	{
		player->bCanOpenEVDoor = true;
	}
}

void AEV_Door::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
	if (player)
	{
		player->bCanOpenEVDoor = false;
	}
}

void AEV_Door::moveLeftDoor(FVector start, FVector end)
{
	timeL += GetWorld()->GetDeltaSeconds() * 0.2;
	timeL = FMath::Clamp(timeL, 0.f, 1.f);
	doorLeft->SetRelativeLocation(FMath::Lerp(start, end, timeL));

	if (!bDoOnce)
	{
		FTimerHandle evHandle;
		GetWorldTimerManager().SetTimer(evHandle, FTimerDelegate::CreateLambda([&](){
			bOpenRightDelay = true;
		}), 2.f, false);
		bDoOnce = true;
	}
}

void AEV_Door::moveRightDoor(FVector start, FVector end)
{
	timeR += GetWorld()->GetDeltaSeconds() * 0.2;
	timeR = FMath::Clamp(timeR, 0.f, 1.f);
	doorRight->SetRelativeLocation(FMath::Lerp(start, end, timeR));
}

