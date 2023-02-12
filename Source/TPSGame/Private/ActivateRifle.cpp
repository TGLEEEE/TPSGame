// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivateRifle.h"
#include <Kismet/GameplayStatics.h>
#include "MyPlayer.h"

void AActivateRifle::GetAmmo()
{
	UGameplayStatics::PlaySound2D(this, getSound, 2.f);
	savePlayer->bIsActivateRifle = true;
	savePlayer->ChangeWeapon(WeaponList::Rifle);
	Destroy();
}
