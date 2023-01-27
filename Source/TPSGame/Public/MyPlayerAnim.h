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
	
public:
	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float forwardVel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float rightVel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bisFalling;
};
