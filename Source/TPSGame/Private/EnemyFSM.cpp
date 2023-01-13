// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//월드에서 플레이어 타깃 가져오기

	//캐스팅

	//소유객체가져오기

}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}

}
//대기상태 - (이후에 플레이어가 나타날때까지) 
void UEnemyFSM::IdleState()
{
	// 시간이 흐르니까
	currentTime += GetWorld()->DeltaTimeSeconds;
	//만약 경과시간이 대기시간을 초과했다면
	if (currentTime > idleDelayTime)
	{
		//3. 이동상태로 전환하고싶다
		mState = EEnemyState::Move;
		//4. 경과시간 초기화
		currentTime = 0;
		UE_LOG(LogTemp, Warning, TEXT("2after move"));
	}
}
//이동상태
void UEnemyFSM::MoveState()
{
	//타깃 목적지

	// 방향

	//방향으로 이동하고싶다

}
//공격상태
void UEnemyFSM::AttackState(){}
//피격상태
void UEnemyFSM::DamageState(){}
//죽음상태
void UEnemyFSM::DieState(){}

