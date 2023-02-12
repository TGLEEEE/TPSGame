// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndingWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UEndingWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_Quit;

	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Score", meta = (BindWidget))
		class UTextBlock* curScore;

	void PrintCurrentScore();

private:
	
	UFUNCTION()
		void QuitGame();

};
