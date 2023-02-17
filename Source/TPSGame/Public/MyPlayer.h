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
	class USkeletalMeshComponent* rocketLauncherFakeComp;
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* rifleComp;
	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* rifleFakeComp;
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
	TSubclassOf<class UUserWidget> onHitFactory;
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
	UUserWidget* onHitUI;
	UPROPERTY()
	USelectWeaponWidget* selectWeaponUI;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* grenadeSetSound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* grenadeGoSound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* spadeSound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* jumpSound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* deathSound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* hurtSound;
	UPROPERTY(EditDefaultsOnly)
	float fireRifleInterval = 0.15;

	bool bIsGrenadeAiming;
	bool bIsKnifeAttackPressing;
	bool bIsReloading;
	bool bIsActivateRifle;
	bool bIsActivateRocketLauncher;
	bool bCanOpenEVDoor;
	class UMyPlayerAnim* anim;
	class AWorldWarGameMode* gm;
	class AAmmo* ammo;
	class AEV_Door* evDoor;
	void ChangeWeapon(WeaponList value);
	void FireGrenade();
	void CrossHit();
	void PlayerDamagedProcess(int value);
	void SpawnBloodEffect(FVector loc, FRotator rot);
	void ReloadWeapon();
	void GetAmmo();

	// 수류탄 궤적 그리기 BP로 구현위해
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector> predictPathLoc;
	UFUNCTION(BlueprintImplementableEvent)
	void DrawGrenadePath();

	UFUNCTION(BlueprintCallable)
	int GetPlayerHP();
	UFUNCTION(BlueprintCallable)
	int GetPlayerMaxHP();	
	UFUNCTION(BlueprintCallable)
	WeaponList GetNowWeapon();

	// 재장전 관련
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammoRifle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammoRifleMax = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammoRocketLauncher;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammoRocketLauncherMax = 1;

	// 탄약
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammoRifleCanReloadCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammoRocketLauncherCanReloadCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammoGrenadeCanReloadCount;

UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
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
	void FireRifle();
	void FireRocketLauncher();
	void FireKnife();
	void Zoom();
	void ZoomOut();
	void ChangeWeaponZooming();
	void PlaySetGrenadeAnim();
	void PlayThrowGrenadeAnim();
	void PredictGrenadePath();
	void PlayAnimReload();
	void SlideRoll();


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
	FTimerHandle selectWeaponHandle;
	FVector dir;
	FVector grenadeFireLoc;
	FVector grenadeLaunchVelocity;

	int playerHP;
	int playerMaxHP = 10;
	float walkSpeed = 400.f;
	float runSpeed = 800.f;
	bool bIsHitUIOn;
	bool bIsZooming;
	bool bReadyToGetAmmo;

};
