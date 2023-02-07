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


protected:
	virtual void BeginPlay() override;

public:
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsStarted;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCanSpawnZombie;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int currentCountdown;

	//
public:
	UPROPERTY(EditAnywhere, Category=MyWidgetSetting)
	TSubclassOf<class UStartWidget> startWidget;

private:
	class UStartWidget* start_UI;
};
