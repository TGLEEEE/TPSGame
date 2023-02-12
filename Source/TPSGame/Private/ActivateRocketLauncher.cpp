// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivateRocketLauncher.h"
#include <Kismet/GameplayStatics.h>
#include "MyPlayer.h"

void AActivateRocketLauncher::GetAmmo()
{
	UGameplayStatics::PlaySound2D(this, getSound, 2.f);
	savePlayer->bIsActivateRocketLauncher = true;
	Destroy();
}
