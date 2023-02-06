// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include <Components/CapsuleComponent.h>
#include "Components/BoxComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyPreset"));

	//1.스켈레탈메시 데이터로드
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Zoombie/copzombie_l_actisdato_UE.copzombie_l_actisdato_UE'"));
	//1-1스켈레탈 메시 데이터로드 성공시
	if (tempMesh.Succeeded())
	{
		//1-2. 데이터를 할당해준다
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		//1-3. 메시위치와 회전설정campsuleComp
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

		

	}
	//EnemyFSM컴포넌트 추가
	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

	//애니메이션 블루프린트 할당하기
	ConstructorHelpers::FClassFinder<UAnimInstance>tempClass(TEXT("/Script/CoreUObject.Class'/Script/TPSGame.EnemyAnim'"));
	if (tempClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempClass.Class);
	}

	//월드에 배치되거나 스폰될때 자동으로
	//AIController부터 Possess될수 있도록 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 데미지 박스
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage BoxComp"));
	boxComp->SetBoxExtent(FVector(40, 40, 10));
	boxComp->SetupAttachment(RootComponent);
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
	if (player)
	{
		player->PlayerDamagedProcess(1);
	}
}
