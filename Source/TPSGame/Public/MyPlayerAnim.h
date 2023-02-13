// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class TPSGAME_API UMyPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeBeginPlay() override;

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float forwardVel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float rightVel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsFalling;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsKnifeMode;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* fireAnimMontage;
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* grenadeAnimMontage;	
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* knifeAnimMontage;
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* rollslideAnimMontage;
	UPROPERTY(EditDefaultsOnly)
	class USoundBase* reloadRifleSound;
	UPROPERTY(EditDefaultsOnly)
	class USoundBase* reloadRocketSound;
	class AMyPlayer* player;

	UFUNCTION()
	void AnimNotify_Get();
	UFUNCTION()
	void AnimNotify_Throw();
	UFUNCTION()
	void AnimNotify_FirstAttackEnd();
	UFUNCTION()
	void AnimNotify_SecondAttackEnd();
	UFUNCTION()
	void AnimNotify_ReloadRifleEnd();
	UFUNCTION()
	void AnimNotify_PlaySoundReload();
	UFUNCTION()
	void FireAnim(FName sectionName);
	UFUNCTION()
	void PlayGrenadeAnim(FName sectionName);
	UFUNCTION()
	void PlayKnifeAttackAnim(FName sectionName);
	UFUNCTION()
	void PlaySlideRollAnim(FName sectionName);
};
