// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWarGameMode.h"

#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"

#include "StartWidget.h"

void AWorldWarGameMode::BeginPlay()
{
	Super::BeginPlay();

	start_UI = CreateWidget<UStartWidget>(GetWorld(), startWidget);

	if (start_UI != nullptr)
	{
		//생성된 위젯을 뷰포트에 그린다.

		start_UI->AddToViewport();
	}

	//마우스 커설르 화면에 보이게 한다
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	
}

void AWorldWarGameMode::ShowGameOver()
{
	//게임 오버를 화면에 띄운다
	over_UI = CreateWidget<UGameOverWidget>(GetWorld(), gameOverWidget);

	if(over_UI != nullptr)
	{
		over_UI->AddToViewport();
	}
	
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}


