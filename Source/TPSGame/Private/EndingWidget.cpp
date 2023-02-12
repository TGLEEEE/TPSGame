// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingWidget.h"
#include "Components/TextBlock.h"
#include "WorldWarGameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UEndingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	btn_Quit->OnClicked.AddDynamic(this, &UEndingWidget::QuitGame);
}

void UEndingWidget::PrintCurrentScore()
{
	AWorldWarGameMode* myGM = Cast<AWorldWarGameMode>(UGameplayStatics::GetGameMode(this));

	if (myGM != nullptr)
	{
		// 현재 점수(정수) -> FText (문자열) 형태로 변환한다.
		FText scoreText = FText::AsNumber(myGM->GetCurrentScore());

		//curScore 텍스트 블록의 값으로 설정한다.
		curScore->SetText(scoreText);
	}
}

void UEndingWidget::QuitGame()
{
	//앱을 종료한다
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
}
