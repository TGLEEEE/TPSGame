// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	//랜덤생성시간 구하기
	float createTime = FMath::RandRange(minTime, maxTime);

	//2.Timer Manager한테 알람 등록
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);

}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::CreateEnemy()
{
	//랜덤 위치구하기
	int index = FMath::RandRange(0, spawnPoints.Num() - 1);
	//점 생성 및배치하기
	GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[index]->GetActorLocation(), FRotator(0));

	//currentTime += GetWorld()->DeltaTimeSeconds;
	//if (currentTime > waveTime)
	//{
	//다시 랜덤 시간에 CreateEnemy함수가 호출되도록 나이머 설정
	float createTimer = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTimer);
	//}

}
