// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include <Components/SphereComponent.h>
#include "MyPlayer.h"

// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Range"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(200.f);
	sphereComp->SetCollisionProfileName(TEXT("PickupPreset"));

	ConstructorHelpers::FObjectFinder<USoundBase>tempGetSound(TEXT("/Script/Engine.SoundWave'/Game/Assets/BGM/soundGet.soundGet'"));
	if (tempGetSound.Succeeded())
	{
		getSound = tempGetSound.Object;
	}
}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();

	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAmmo::OnOverlap);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &AAmmo::EndOverlap);
}

// Called every frame
void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmo::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
	if (player)
	{
		savePlayer = player;
		bIsOverlaping = true;
		//UE_LOG(LogTemp, Warning, TEXT("overlap"));
	}
}

void AAmmo::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
	if (player)
	{
		bIsOverlaping = false;
		//UE_LOG(LogTemp, Warning, TEXT("overlapend"));
	}
}

void AAmmo::GetAmmo()
{

}

