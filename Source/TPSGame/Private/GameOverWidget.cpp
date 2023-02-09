// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	btn_ReStart->OnClicked.AddDynamic(this,&UGameOverWidget::ReStartGame);
	btn_Quit->OnClicked.AddDynamic(this, &UGameOverWidget::QuitGame);
}

void UGameOverWidget::ReStartGame()
{
	//레벨을 다시 로드한다 
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMap"));

	//현재 위젯은 제거한다
	this->RemoveFromParent();
}

void UGameOverWidget::QuitGame()
{
	//앱을 종료한다
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
}
