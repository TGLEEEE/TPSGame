// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnim.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"

void UEnemyAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	me = Cast<AEnemy>(TryGetPawnOwner());
}

void UEnemyAnim::OnEndAttackAnimation()
{
	bAttackPlay = false;
}

void UEnemyAnim::AnimNotify_EnemyAttackStart()
{
	if (me)
	{
		me->boxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		//UE_LOG(LogTemp, Warning, TEXT("collision on"));
	}
}

void UEnemyAnim::AnimNotify_EnemyAttackEnd()
{
	if (me)
	{
		me->boxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//UE_LOG(LogTemp, Warning, TEXT("collision off"));
	}
}
