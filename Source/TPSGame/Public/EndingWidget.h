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
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_Quit;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_EnterName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Score", meta = (BindWidget))
	class UTextBlock* curScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Score", meta = (BindWidget))
	class UTextBlock* recordFirst;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Score", meta = (BindWidget))
	class UTextBlock* recordSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Score", meta = (BindWidget))
	class UTextBlock* recordThird;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Score", meta = (BindWidget))
	class UTextBlock* recordFirstName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Score", meta = (BindWidget))
	class UTextBlock* recordSecondName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Score", meta = (BindWidget))
	class UTextBlock* recordThirdName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Score", meta = (BindWidget))
	class UEditableText* InputText;
	UFUNCTION()
	void PrintCurrentScore();
	UFUNCTION()
	void EnterName();

private:
	
	UFUNCTION()
		void QuitGame();

};
