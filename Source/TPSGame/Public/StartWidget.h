// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* btn_Start;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* btn_Quit;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();

};
