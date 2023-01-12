// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UCLASS()
class TPSGAME_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* playerSpringArm;
	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* playerCamera;

	void InputAxisLookUp(float value);
	void InputAxisTurnRight(float value);
	void InputAxisMoveVertical(float value);
	void InputAxisMoveHorizontal(float value);
	void InputActionJump();

private:
	FVector dir;
};
