// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_ReStart;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_Quit;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
		void ReStartGame();

	UFUNCTION()
		void QuitGame();

};
