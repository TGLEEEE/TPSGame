// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWarGameMode.h"

#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "EndingWidget.h"
#include "StartWidget.h"
#include "BGMManager.h"
#include "EngineUtils.h"
#include "SaveScore.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

void AWorldWarGameMode::BeginPlay()
{
	Super::BeginPlay();

	start_UI = CreateWidget<UStartWidget>(GetWorld(), startWidget);
	over_UI = CreateWidget<UGameOverWidget>(GetWorld(), gameOverWidget);
	ending_UI = CreateWidget<UEndingWidget>(GetWorld(), endingwWidget);
	
	if (start_UI != nullptr)
	{
		//생성된 위젯을 뷰포트에 그린다.

		start_UI->AddToViewport();
	}

	//마우스 커설르 화면에 보이게 한다
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	for(auto actor : TActorRange<ABGMManager>(GetWorld()))
	{
		bgm = actor;
	}
}

void AWorldWarGameMode::ShowGameOver()
{
	// 배경음악 재생
	bgm->PlayBGMDie();
	// 카운트다운 타이머 취소
	GetWorldTimerManager().ClearTimer(countdownHandle);
	if(over_UI != nullptr)
	{
		over_UI->AddToViewport();
	}
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void AWorldWarGameMode::ShowEnding()
{
	// 순위점수 불러오고 업데이트 후 저장
	LoadScore();
//	RecordScore();
//	SaveScore();

	// 배경음악 재생
	bgm->PlayBGMClear();
	// 카운트다운 타이머 취소
	GetWorldTimerManager().ClearTimer(countdownHandle);
	if (ending_UI != nullptr)
	{
		ending_UI->AddToViewport();
		ending_UI->PrintCurrentScore();
		if (currentScore < scoreThird)
		{
			ending_UI->InputText->SetVisibility(ESlateVisibility::Hidden);
			ending_UI->btn_EnterName->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}


void AWorldWarGameMode::CountdownTimer(int time)
{
	currentCountdown = time;
	GetWorldTimerManager().SetTimer(countdownHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (currentCountdown > 0)
			{
				currentCountdown--;
				if (currentCountdown == 1 && stage == 2)
				{
					UGameplayStatics::SetGlobalTimeDilation(this, 0.3);
				}
			}
			else
			{
				currentCountdown = 0;
				bCanSpawnZombie = !bCanSpawnZombie;
				GetWorldTimerManager().ClearTimer(countdownHandle);
			}
		}), 1.f, true);
}

void AWorldWarGameMode::AddScore(int32 count)
{
	currentScore += count;
}

void AWorldWarGameMode::RecordScore()
{
	if (currentScore >= scoreFirst)
	{
		scoreThird = scoreSecond;
		scoreSecond = scoreFirst;
		scoreFirst = currentScore;

		scoreThirdName = scoreSecondName;
		scoreSecondName = scoreFirstName;
		scoreFirstName = currentName;
	}
	else if (currentScore >= scoreSecond)
	{
		scoreThird = scoreSecond;
		scoreSecond = currentScore;

		scoreThirdName = scoreSecondName;
		scoreSecondName = currentName;
	}
	else if (currentScore >= scoreThird)
	{
		scoreThird = currentScore;

		scoreThirdName = currentName;
	}
}

void AWorldWarGameMode::LoadScore()
{
	USaveScore* loadDataInstance = Cast<USaveScore>(UGameplayStatics::CreateSaveGameObject(USaveScore::StaticClass()));
	if (loadDataInstance)
	{
		loadDataInstance->slotName = "ScoreData";
		loadDataInstance->saveIndex = 0;

		loadDataInstance = Cast<USaveScore>(UGameplayStatics::LoadGameFromSlot(loadDataInstance->slotName, loadDataInstance->saveIndex));
		if (loadDataInstance)
		{
			scoreFirst = loadDataInstance->scoreFirst;
			scoreSecond = loadDataInstance->scoreSecond;
			scoreThird = loadDataInstance->scoreThird;

			scoreFirstName = loadDataInstance->scoreFirstName;
			scoreSecondName = loadDataInstance->scoreSecondName;
			scoreThirdName = loadDataInstance->scoreThirdName;
		}
	}
}

void AWorldWarGameMode::SaveScore()
{
	USaveScore* scoreDataInstance = Cast<USaveScore>(UGameplayStatics::CreateSaveGameObject(USaveScore::StaticClass()));
	if (scoreDataInstance)
	{
		scoreDataInstance->slotName = "ScoreData";
		scoreDataInstance->saveIndex = 0;

		scoreDataInstance->scoreFirst = scoreFirst;
		scoreDataInstance->scoreSecond = scoreSecond;
		scoreDataInstance->scoreThird = scoreThird;

		scoreDataInstance->scoreFirstName = scoreFirstName;
		scoreDataInstance->scoreSecondName = scoreSecondName;
		scoreDataInstance->scoreThirdName = scoreThirdName;

		UGameplayStatics::SaveGameToSlot(scoreDataInstance, scoreDataInstance->slotName, scoreDataInstance->saveIndex);
	}
}

