// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UEndingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	btn_Quit->OnClicked.AddDynamic(this, &UEndingWidget::QuitGame);
}

void UEndingWidget::QuitGame()
{
	//앱을 종료한다
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
}
