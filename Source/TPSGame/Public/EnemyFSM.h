// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

//사용할 상태의 정의
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSGAME_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//상태처리 함수선언
	//상대변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mState = EEnemyState :: Idle;
	
	//대기상태
	void IdleState();
	//이동상태
	void MoveState();
	//공격상태
	void AttackState();
	//피격상태
	void DamageState();
	//죽음상태
	void DieState();

	//대기시간
	UPROPERTY(EditDefaultsOnly, Category=FSM)
	float idleDelayTime = 2; 
	//경과시간
	float currentTime = 0;
	
	//타깃
	//UPROPERTY(VisibleAnywhere,Category=FSM)

	//소유액터
	UPROPERTY()
	class AEnemy*me;

	//공격범위 
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackRange = 150.0f;

	
		
};
