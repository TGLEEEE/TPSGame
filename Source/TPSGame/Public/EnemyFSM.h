// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyPlayer.h"
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
	Climb,
	Dive,
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
	bool bDoOnce;
	bool bDoNot;

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
	//오르기
	void ClimbState();
	

	//대기시간
	UPROPERTY(EditDefaultsOnly, Category=FSM)
	float idleDelayTime = 0.6f; 
	//경과시간
	float currentTime = 0;
	
	//타깃
	UPROPERTY(VisibleAnywhere,Category=FSM)
		class AMyPlayer* target;

	//소유액터
	UPROPERTY()
	class AEnemy* me;

	//공격범위 
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackRange = 150.0f;

	//공격 대기시간 
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackDelayTime= 2.0f;

	//피격 알림 이벤트 함수
	void OnDamageProcess(int val);

	//체력
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = FSM)
	int32 hp = 3;

	//피격상태 대기시간
	UPROPERTY(EditAnywhere, Category=FSM)
	float damageDelayTime = 0.4f;

	//사용중인 애니메이션블루프린트
	UPROPERTY()
	class UEnemyAnim* anim;

	
	//Enemy를 소유하고 있는 AlController
	UPROPERTY()
		class AAIController* ai;

	//아래로 사라지는 속도
	UPROPERTY(EditAnywhere, Category = FSM)
		float dieSpeed = 50.0f;

	//적의 움직임 제어 
	bool canMove = true;

	//시체 남기는 시간
	float dieDelayTime = 10.0f;

	FTimerHandle aiTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundCue* idleSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundCue* damageSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
		class USoundCue* deadSound;
	
};
