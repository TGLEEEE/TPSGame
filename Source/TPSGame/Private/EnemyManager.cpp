// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"
#include "WorldWarGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "SpawnPoint.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	spawnPoints.Empty();
	// 시작시 위치목록을 채운다
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), spawnPoints);


	//랜덤생성시간 구하기
	createTime = FMath::RandRange(minTime, maxTime);

	//2.Timer Manager한테 알람 등록
	//GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
	gm = Cast<AWorldWarGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
/*
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > waveTime)
	{
		CreateEnemy();
	}
	currentTime = 0;
*/

	if (gm->bCanSpawnZombie && gm->stage == 1)
	{
		GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
		gm->stage++;
	}

	if (!gm->bCanSpawnZombie && gm->stage == 2)
	{
		GetWorldTimerManager().ClearTimer(spawnTimerHandle);
		gm->stage++;
	}

	if (!bDoOnce && gm->stage == 3)
	{
		bDoOnce = true;
		gm->ShowEnding();
	}
}


void AEnemyManager::CreateEnemy()
{
	{
		//랜덤 위치구하기
		int index = FMath::RandRange(0, spawnPoints.Num() - 1);
		//점 생성 및배치하기
		GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[index]->GetActorLocation(), FRotator(0));

		//다시 랜덤 시간에 CreateEnemy함수가 호출되도록 나이머 설정
		float createTimer = FMath::RandRange(minTime, maxTime);
		GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTimer);
	}
}

