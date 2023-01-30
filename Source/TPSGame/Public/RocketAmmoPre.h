// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RocketAmmo.h"
#include "RocketAmmoPre.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API ARocketAmmoPre : public ARocketAmmo
{
	GENERATED_BODY()

public:
	ARocketAmmoPre();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FTimerHandle fireTimer;
	void SpawnFireAmmo();
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARocketAmmo> fireAmmoFactory;
};
