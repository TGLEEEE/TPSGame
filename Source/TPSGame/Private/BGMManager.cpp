// Fill out your copyright notice in the Description page of Project Settings.


#include "BGMManager.h"
#include <Components/AudioComponent.h>
#include "WorldWarGameMode.h"
#include <Sound/SoundBase.h>

// Sets default values
ABGMManager::ABGMManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bgmStage1 = CreateDefaultSubobject<UAudioComponent>(TEXT("BGM Stage1"));
	ConstructorHelpers::FObjectFinder<USoundBase>tempBGMStage1(TEXT("/Script/Engine.SoundWave'/Game/Assets/BGM/AtStart.AtStart'"));
	if (tempBGMStage1.Succeeded())
	{
		bgmStage1->SetSound(tempBGMStage1.Object);
	}
	bgmStage1->SetVolumeMultiplier(0.8f);

	bgmStage2 = CreateDefaultSubobject<UAudioComponent>(TEXT("BGM Stage2"));
	ConstructorHelpers::FObjectFinder<USoundBase>tempBGMStage2(TEXT("/Script/Engine.SoundWave'/Game/Assets/BGM/MainPlay_1.MainPlay_1'"));
	if (tempBGMStage2.Succeeded())
	{
		bgmStage2->SetSound(tempBGMStage2.Object);
	}
	bgmStage2->SetVolumeMultiplier(0.8f);

	bgmDie = CreateDefaultSubobject<UAudioComponent>(TEXT("BGM Die"));
	ConstructorHelpers::FObjectFinder<USoundBase>tempBGMDie(TEXT("/Script/Engine.SoundWave'/Game/Assets/BGM/SadEnding_1.SadEnding_1'"));
	if (tempBGMDie.Succeeded())
	{
		bgmDie->SetSound(tempBGMDie.Object);
	}
	bgmDie->SetTickableWhenPaused(true);
	bgmDie->SetUISound(true);

	bgmClear = CreateDefaultSubobject<UAudioComponent>(TEXT("BGM Clear"));
	ConstructorHelpers::FObjectFinder<USoundBase>tempBGMClear(TEXT("/Script/Engine.SoundWave'/Game/Assets/BGM/ClearGame.ClearGame'"));
	if (tempBGMClear.Object)
	{
		bgmClear->SetSound(tempBGMClear.Object);
	}
	bgmClear->SetTickableWhenPaused(true);
	bgmClear->SetUISound(true);
	bgmClear->SetVolumeMultiplier(0.8f);
}

// Called when the game starts or when spawned
void ABGMManager::BeginPlay()
{
	Super::BeginPlay();
	gm = Cast<AWorldWarGameMode>(GetWorld()->GetAuthGameMode());
	bgmStage1->Stop();
	bgmStage2->Stop();
	bgmDie->Stop();
	bgmClear->Stop();
}

// Called every frame
void ABGMManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (gm->stage == 1 && OncePlayByStage == 1)
	{
		OncePlayByStage++;
		bgmStage1->Play();
	}
	else if(gm->stage == 2 && OncePlayByStage == 2)
	{
		OncePlayByStage++;
		bgmStage1->Stop();
		bgmStage2->Play();
	}
}

void ABGMManager::PlayBGMDie()
{
	bgmStage2->Stop();
	bgmDie->Play();
}

void ABGMManager::PlayBGMClear()
{
	bgmStage2->Stop();
	bgmClear->Play();
}

