// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoRifle.h"
#include "MyPlayer.h"
#include <Kismet/GameplayStatics.h>

void AAmmoRifle::GetAmmo()
{
	if (bIsOverlaping)
	{
		UGameplayStatics::PlaySound2D(this, getSound, 2.f);
		savePlayer->ammoRifleCanReloadCount += 2;
		Destroy();
	}
}
