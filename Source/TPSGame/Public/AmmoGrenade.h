// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ammo.h"
#include "AmmoGrenade.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API AAmmoGrenade : public AAmmo
{
	GENERATED_BODY()
public:
	virtual void GetAmmo() override;
};
