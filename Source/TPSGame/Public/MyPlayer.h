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
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* knifeComp;
	UPROPERTY(EditDefaultsOnly)
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
	bool bIsGrenadeAiming;
	bool bIsKnifeAttackPressing;
	class UMyPlayerAnim* anim;

	int GetPlayerHP();
	void SetPlayerHP(int hp);
	void FireGrenade();
	void CrossHit();

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
	void ChangeWeapon(WeaponList value);
	void FireRifle();
	void FireRocketLauncher();
	void FireKnife();
	void Zoom();
	void ZoomOut();
	void ChangeWeaponZooming();
	void PlaySetGrenadeAnim();
	void PlayThrowGrenadeAnim();
	void PredictGrenadePath();

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
	WeaponList nowWeapon;
	FTimerHandle rifleTimerhandle;
	FTimerHandle crossHitTimerhandle;
	FVector dir;
	FVector grenadeFireLoc;
	FVector grenadeLaunchVelocity;

	int playerHP = 100;
	bool bIsHitUIOn;
	bool bIsZooming;
	float walkSpeed = 400.f;
	float runSpeed = 800.f;

};
