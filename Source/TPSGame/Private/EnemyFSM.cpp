// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "Enemy.h"
#include "AIController.h"
#include "MyPlayer.h"
#include "EnemyAnim.h"
#include "Components/CapsuleComponent.h"
#include "NavigationSystem.h"
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
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), AMyPlayer::StaticClass());
	//AMyPlayer타입으로캐스팅
	target = Cast<AMyPlayer>(actor);
	//소유객체가져오기
	me = Cast<AEnemy>(GetOwner());

	//UEnemyAnim*할당
	anim = Cast<UEnemyAnim>(me->GetMesh()->GetAnimInstance());

	//AAIController 할당하기
	ai = Cast<AAIController>(me->GetController());

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
		AttackState();
		break;
	case EEnemyState::Damage:
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
		//UE_LOG(LogTemp, Warning, TEXT("2after move"));

		//애니메이션 상태 동기화
		anim->animState = mState;
	}


}
//이동상태
void UEnemyFSM::MoveState()
{
 	if (!canMove)
	{
		return;
 	}
	//타깃 목적지
	FVector destination = target->GetActorLocation();
	// 방향
	FVector dir = destination - me->GetActorLocation();

	//방향으로 이동하고싶다
	//me->AddMovementInput(dir.GetSafeNormal());
	ai->MoveToLocation(destination);


/*
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	FPathFindingQuery query;

	FAIMoveRequest req;

	req.SetAcceptanceRadius(100);

	req.SetGoalLocation(destination);

	ai->BuildPathfindingQuery(req, query);

	FPathFindingResult r = ns->FindPathSync(query);

	if (r.Result == ENavigationQueryResult::Success)
	{
		ai->MoveToLocation(destination);
	}
	*/

	//타깃과 가까워지면 공격상태로 전환하고싶다
	//1. 만약 거리가 공격범위안에 들어오면
	if (dir.Size() < attackRange)
	{
		ai->StopMovement();
		//2.공격상태로 전환하고싶다
		mState = EEnemyState::Attack;
		//애니메이션 상태 동기화
		anim->animState = mState;
		//공격애니메이션 재생활성화
		anim->bAttackPlay = true;
		//공격상태전환시 대기시간이 바로 끝나도록 처리
		currentTime = attackDelayTime;

	}
	


	//목저ㅗㄱ지 
}
//공격상태
void UEnemyFSM::AttackState()
{
	

	    //목표: 일정 시간에 한번씩 공격하고싶다
	    //1. 시간이 흘러야한다
	    currentTime += GetWorld()->DeltaTimeSeconds;
		//2. 공격시간이 됐을때
		if (currentTime > attackDelayTime)
		{
	
			//3. 공격하고싶다

			//---------
			currentTime = 0;
			anim->bAttackPlay = true;
	
		}

	
// 	    //목표: 타깃이 공격 범위를 벗어나면 상태를 이동으로 전환하고싶다
		//1. 타깃과의 거리가 필요
		float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
		//2.타깃과의 거리가 공격범위를 벗어 났을때
		if (distance > attackRange)
		{
			//3. 상태를 이동으로 전환하고 싶다
			mState = EEnemyState::Move;
			//애니메이션 상태 동기화
		anim->animState = mState;
		}
	

}
//피격상태
void UEnemyFSM::DamageState()
{
	//1.시간이 흘렀으니까
	currentTime += GetWorld()->DeltaTimeSeconds;
	//2.만약 경과시간이 대기시간을 초과했다면 
	if (currentTime > damageDelayTime)
	{
		//3.대기상태로전환하고싶다
		mState = EEnemyState::Idle;
		//경과시간초기화
		currentTime = 0;
		//애니메이션 상태 동기화
		anim->animState = mState;

	}
}
//죽음상태
void UEnemyFSM::DieState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > dieDelayTime)
	{
		//계속 아래로 내려가고싶다
		//등속운동공식 P = P0+vt
		FVector P0 = me->GetActorLocation();
		FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
		FVector P = P0 + vt;
		me->SetActorLocation(P);

		//만약2미터이상내려왔다면
		if (P.Z < -200.0f)
		{
			//제거시킨다
			me->Destroy();
		}

	}
}

//피격알림 이벤트 함수
void UEnemyFSM::OnDamageProcess(int val)
{
	UE_LOG(LogTemp, Warning, TEXT("enemy hited"));
	//체력감소 
	hp -= val;
	//만약에 체력이 남아있다면 
	if (hp > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("?"));
		//상태를 피격으로 전환
		mState = EEnemyState::Damage;

		currentTime = 0;
		//피격애니메이션 재생
		int32 index = FMath::RandRange(0, 1);
		FString sectionName = FString::Printf(TEXT("Damage%d"), index);
		anim->PlayDamageAnim(FName(*sectionName));

	}
	//그렇지않으먄
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("zugum"));
		//상태를 죽음으로 전환
		mState = EEnemyState::Die;
		//캡슐 충돌체 비활성화
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//죽음 애니메이션 재생
		anim->PlayDamageAnim(TEXT("Die"));

	}

	//애니메이션상태 동기화
	anim->animState = mState;

	ai->StopMovement();
}

