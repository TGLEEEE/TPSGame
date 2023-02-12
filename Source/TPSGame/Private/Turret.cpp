// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"


// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Comp"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(600.f);
//	sphereComp->SetCollisionProfileName(TEXT(""));

	base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	base->SetupAttachment(RootComponent);
	base->SetRelativeScale3D(FVector(0.8f));
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempBase(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Weapon/TurretFBXs/TurretBase.TurretBase'"));
	if (tempBase.Succeeded())
	{
		base->SetStaticMesh(tempBase.Object);
	}

	top = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
	top->SetupAttachment(base);
	top->SetRelativeScale3D(FVector(0.8f));
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempTop(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Weapon/TurretFBXs/TurretTop.TurretTop'"));
	if (tempTop.Succeeded())
	{
		top->SetStaticMesh(tempTop.Object);
	}
	top->SetRelativeLocation(FVector(0, 0, 180.f));

	barrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
	barrel->SetupAttachment(top);
	barrel->SetRelativeScale3D(FVector(0.8f));
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempBarrel(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Weapon/TurretFBXs/TurretBarrel.TurretBarrel'"));
	if (tempBarrel.Succeeded())
	{
		barrel->SetStaticMesh(tempBarrel.Object);
	}

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlap);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &ATurret::EndOverlap);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (target == nullptr)
	{
		FindBestTarget();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("change direction"));
		FVector direction = target->GetActorLocation() - GetActorLocation();
		direction.Normalize();
		top->SetRelativeRotation(FRotator(0, direction.Z, 0));
	}
}

void ATurret::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
//	UE_LOG(LogTemp, Warning, TEXT("begin overlap"));

	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	if (enemy)
	{
		targetList.Add(enemy);
	}
}

void ATurret::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
//	UE_LOG(LogTemp, Warning, TEXT("end overlap"));

	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	if (enemy)
	{
		targetList.Remove(enemy);
	}
}

void ATurret::FindBestTarget()
{
	if (targetList.Num() == 0)
	{
		return;
	}
	targetDistanceList.Empty();
	// 타겟리스트의 모든 대상과의 거리를 계산한 후
	for (int i = 0; i < targetList.Num(); i++)
	{
		targetDistanceList[i] = (GetActorLocation() - targetList[i]->GetActorLocation()).Size();
	}
	// 가장 가까운 적을 타겟으로 삼는다
	double tempFloat = targetDistanceList[0];
	for (int i = 1; i < targetDistanceList.Num(); i++)
	{
		if (tempFloat > targetDistanceList[i])
		{
			tempFloat = targetDistanceList[i];
		}
	}
	target = targetList[targetDistanceList.Find(tempFloat)];
}

