// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingWidget.h"
#include "Components/TextBlock.h"
#include "WorldWarGameMode.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UEndingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	btn_Quit->OnClicked.AddDynamic(this, &UEndingWidget::QuitGame);
	btn_EnterName->OnClicked.AddDynamic(this, &UEndingWidget::EnterName);
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

		// 순위점수 출력
		FText recordFirstText = FText::AsNumber(myGM->scoreFirst);
		FText recordSecondText = FText::AsNumber(myGM->scoreSecond);
		FText recordThirdText = FText::AsNumber(myGM->scoreThird);
		recordFirst->SetText(recordFirstText);
		recordSecond->SetText(recordSecondText);
		recordThird->SetText(recordThirdText);

		// 점수별 이름 출력
		recordFirstName->SetText(FText::FromString(myGM->scoreFirstName));
		recordSecondName->SetText(FText::FromString(myGM->scoreSecondName));
		recordThirdName->SetText(FText::FromString(myGM->scoreThirdName));

	}
}

void UEndingWidget::EnterName()
{
	AWorldWarGameMode* myGM = Cast<AWorldWarGameMode>(UGameplayStatics::GetGameMode(this));
	myGM->currentName =  InputText->GetText().ToString();
	myGM->RecordScore();
	myGM->SaveScore();
	if (myGM->ending_UI)
	{
		myGM->ending_UI->PrintCurrentScore();
	}

	InputText->SetVisibility(ESlateVisibility::Hidden);
	btn_EnterName->SetVisibility(ESlateVisibility::Hidden);
}

void UEndingWidget::QuitGame()
{
	//앱을 종료한다
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
}
