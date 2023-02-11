// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoGrenade.h"
#include "MyPlayer.h"
#include <Kismet/GameplayStatics.h>

void AAmmoGrenade::GetAmmo()
{
	if (bIsOverlaping)
	{
		UGameplayStatics::PlaySound2D(this, getSound, 2.f);
		savePlayer->ammoGrenadeCanReloadCount += 3;
		Destroy();
	}
}
