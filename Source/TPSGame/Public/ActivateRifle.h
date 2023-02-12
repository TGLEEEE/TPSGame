// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ammo.h"
#include "ActivateRifle.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API AActivateRifle : public AAmmo
{
	GENERATED_BODY()
public:
	virtual void GetAmmo() override;
};
