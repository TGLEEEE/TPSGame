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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USplineComponent* splineComp;
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
	TSubclassOf<class UUserWidget> warningTextFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USelectWeaponWidget> selectWeaponWidgetFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> knifeEffect;
	UPROPERTY()
	UUserWidget* crossIdleUI;
	UPROPERTY()
	UUserWidget* crossZoomUI;
	UPROPERTY()
	UUserWidget* crossHitUI;
	UPROPERTY()
	UUserWidget* warningTextUI;
	UPROPERTY()
	USelectWeaponWidget* selectWeaponUI;
	UPROPERTY(EditDefaultsOnly)
	float fireRifleInterval = 0.15;
	bool bIsGrenadeAiming;
	bool bIsKnifeAttackPressing;
	class UMyPlayerAnim* anim;
	class AWorldWarGameMode* gm;

	void FireGrenade();
	void CrossHit();
	void CountdownTimer(int time);
	void PlayerDamagedProcess(int value);
	void SpawnBloodEffect(FVector loc, FRotator rot);

	// 수류탄 궤적 그리기 BP로 구현위해
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> predictPathLoc;
	UFUNCTION(BlueprintImplementableEvent)
	void DrawGrenadePath();

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
	UPROPERTY(EditAnywhere)
	UParticleSystem* bloodFx;


	WeaponList nowWeapon;
	FTimerHandle rifleTimerhandle;
	FTimerHandle crossHitTimerhandle;
	FTimerHandle countdownHandle;
	FTimerHandle selectWeaponHandle;
	FVector dir;
	FVector grenadeFireLoc;
	FVector grenadeLaunchVelocity;

	int playerHP = 20;
	bool bIsHitUIOn;
	bool bIsZooming;
	float walkSpeed = 400.f;
	float runSpeed = 800.f;

};
