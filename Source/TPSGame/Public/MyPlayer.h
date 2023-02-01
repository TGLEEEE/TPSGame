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

	UPROPERTY()
	class USpringArmComponent* playerSpringArm;
	UPROPERTY()
	class UCameraComponent* playerCamera;
	UPROPERTY()
	class USkeletalMeshComponent* rocketLauncherComp;
	UPROPERTY()
	class USkeletalMeshComponent* rifleComp;
	UPROPERTY()
	class UStaticMeshComponent* knifeComp;
	UPROPERTY()
	class UStaticMeshComponent* grenadeComp;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARocketAmmo> rocketFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGrenade> grenadeFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> crossIdleFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> crossZoomFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> crossHitFactory;
	UPROPERTY(EditDefaultsOnly)
	float fireRifleInterval = 0.15;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayGrenadeAnimMontage(FName sectionName);

	void SetPlayerHP(int hp);
	int GetPlayerHP();

private:

	void InputAxisLookUp(float value);
	void InputAxisTurnRight(float value);
	void InputAxisMoveVertical(float value);
	void InputAxisMoveHorizontal(float value);
	void InputActionJump();
	void InputActionFire();
	void InputActionFireReleased();
	void InputActionRun();
	void InputActionRunReleased();
	void ArmRocketLauncher();
	void ArmRifle();
	void ArmKnife();
	void ArmGrenade();
	void ChangeWeapon(WeaponList value);
	void FireRifle();
	void FireRocketLauncher();
	void FireKnife();
	void FireGrenade();
	void Zoom();
	void ZoomOut();
	void CrossHit();
	void ChangeWeaponZooming();

	UFUNCTION()
	void KnifeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	UParticleSystem* bulletEffectFactory;
	UPROPERTY(EditAnywhere)
	UAnimSequence* animRifleFire;
	UPROPERTY(EditAnywhere)
	UAnimSequence* animRockerLauncherFire;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase>rocketCamShakeFactory;

	UPROPERTY()
	UUserWidget* crossIdleUI;
	UPROPERTY()
	UUserWidget* crossZoomUI;
	UPROPERTY()
	UUserWidget* crossHitUI;
	FVector dir;
	WeaponList nowWeapon;
	FTimerHandle rifleTimerhandle;
	FTimerHandle crossHitTimerhandle;

	int playerHP = 100;
	bool bisHitUIOn;
	bool bisZooming;
	float walkSpeed = 400.f;
	float runSpeed = 800.f;
};
