// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WorldWarGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API AWorldWarGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	bool bIsStarted;
};
