// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UENUM(BlueprintType)
enum class WeaponList : uint8
{
	Rifle,
	RocketLauncher,
	Knife,
	Grenade
};

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
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* rocketLauncherComp;
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* rifleComp;
	UPROPERTY(EditDefaultsOnly, Category=PlayerSettings)
	TSubclassOf<class ARocketAmmo> BulletFactory;
	UPROPERTY(EditDefaultsOnly, Category=PlayerSettings)
	UParticleSystem* bulletEffectFactory;
	UPROPERTY(EditDefaultsOnly, Category=PlayerSettings)
	float fireRifleInterval = 0.2;

	void InputAxisLookUp(float value);
	void InputAxisTurnRight(float value);
	void InputAxisMoveVertical(float value);
	void InputAxisMoveHorizontal(float value);
	void InputActionJump();
	void InputActionFire();
	void InputActionFireReleased();

private:

	void ArmRocketLauncher();
	void ArmRifle();
	void ArmKnife();
	void ArmGrenade();
	void ChangeWeapon(WeaponList value);
	void FireRifle();
	void FireRocketLauncher();
	void FireKnife();
	void FireGrenade();

	FVector dir;
	WeaponList nowWeapon;
	FTimerHandle rifleTimerhandle;
};
