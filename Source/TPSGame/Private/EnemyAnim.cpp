// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnim.h"

#include "Enemy.h"
#include "Components/BoxComponent.h"

void UEnemyAnim::OnEndAttackAnimation()
{
	bAttackPlay = false;
}
