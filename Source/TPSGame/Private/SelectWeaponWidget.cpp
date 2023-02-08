// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectWeaponWidget.h"

void USelectWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(selectRifle);
	PlayAnimation(selectRocketLauncher);
	PlayAnimation(selectSpade);
	PlayAnimation(selectGrenade);
}

