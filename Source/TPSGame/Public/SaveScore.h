// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveScore.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API USaveScore : public USaveGame
{
	GENERATED_BODY()

public:
	USaveScore();

public:

	UPROPERTY()
	FString slotName;
	UPROPERTY()
	int32 saveIndex;
	UPROPERTY()
	int32 scoreFirst;
	UPROPERTY()
	int32 scoreSecond;
	UPROPERTY()
	int32 scoreThird;
	UPROPERTY()
	FString scoreFirstName;
	UPROPERTY()
	FString scoreSecondName;
	UPROPERTY()
	FString scoreThirdName;
};
