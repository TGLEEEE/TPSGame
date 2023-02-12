// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoRocket.h"
#include "MyPlayer.h"
#include <Kismet/GameplayStatics.h>

void AAmmoRocket::GetAmmo()
{
	if (bIsOverlaping)
	{
		UGameplayStatics::PlaySound2D(this, getSound, 2.f);
		savePlayer->ammoRocketLauncherCanReloadCount += 2;
		Destroy();
	}
}