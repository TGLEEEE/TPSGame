// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "RocketAmmo.h"
#include <Kismet/GameplayStatics.h>
#include "Enemy.h"
#include <Particles/ParticleSystem.h>
#include <Blueprint/UserWidget.h>
#include <Components/CapsuleComponent.h>
#include <Components/StaticMeshComponent.h>
#include "EnemyFSM.h"
#include "Grenade.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 캐릭터 메시
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Player/character.character'"));
	if (mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(mesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerPreset"));
	// 스프링암
	playerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("playerSpringArm"));
	playerSpringArm->SetupAttachment(RootComponent);
	playerSpringArm->TargetArmLength = 250;
	// 카메라
	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("playerCamera"));
	playerCamera->SetupAttachment(playerSpringArm);
	playerCamera->SetRelativeLocation(FVector(0, 50, 100));

	bUseControllerRotationYaw = true;
	playerSpringArm->bUsePawnControlRotation = true;
	playerCamera->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 로켓런처
	rocketLauncherComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Rocket Launcher Mesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempRocketLauncher(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Weapon/MilitaryWeapSilver/Weapons/Rocket_Launcher_A.Rocket_Launcher_A'"));
	if (tempRocketLauncher.Succeeded())
	{
		rocketLauncherComp->SetSkeletalMesh(tempRocketLauncher.Object);
	}
	rocketLauncherComp->SetupAttachment(GetMesh());
	rocketLauncherComp->SetRelativeLocation(FVector(-30, 0, 120));

	ConstructorHelpers::FObjectFinder<UParticleSystem>tempRocketMuzzleFront(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Weapon/MilitaryWeapSilver/FX/P_RocketLauncher_MuzzleFlash_Front_01.P_RocketLauncher_MuzzleFlash_Front_01'"));
	if (tempRocketMuzzleFront.Succeeded())
	{
		rocketMuzzleFront = tempRocketMuzzleFront.Object;
	}
	ConstructorHelpers::FObjectFinder<UParticleSystem>tempRocketMuzzleBack(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Weapon/MilitaryWeapSilver/FX/P_RocketLauncher_MuzzleFlash_Rear_01.P_RocketLauncher_MuzzleFlash_Rear_01'"));
	if (tempRocketMuzzleBack.Succeeded())
	{
		rocketMuzzleBack = tempRocketMuzzleBack.Object;
	}
	// 라이플
	rifleComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Rifle Mesh"));
	rifleComp->SetupAttachment(GetMesh());
	rifleComp->SetRelativeLocation(FVector(-30, 0, 120));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempRifle(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Weapon/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A'"));
	if (tempRifle.Succeeded())
	{
		rifleComp->SetSkeletalMesh(tempRifle.Object);
	}
	ConstructorHelpers::FObjectFinder<UParticleSystem>tempBulletEffect(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Weapon/MilitaryWeapSilver/FX/P_Impact_Metal_Medium_01.P_Impact_Metal_Medium_01'"));
	if (tempBulletEffect.Succeeded())
	{
		bulletEffectFactory = tempBulletEffect.Object;
	}
	ConstructorHelpers::FObjectFinder<UParticleSystem>tempMuzzleFire(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Weapon/MilitaryWeapSilver/FX/P_AssaultRifle_MuzzleFlash.P_AssaultRifle_MuzzleFlash'"));
	if (tempMuzzleFire.Succeeded())
	{
		rifleMuzzleFire = tempMuzzleFire.Object;
	}
	// 수류탄
	grenadeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Greande Mesh"));
	grenadeComp->SetupAttachment(GetMesh());
	grenadeComp->SetRelativeLocation(FVector(-30, 0, 120));
	ConstructorHelpers::FObjectFinder<UStaticMesh>tempGrenade(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Weapon/MilitaryWeapSilver/Weapons/GrenadeLauncherA_Ammo.GrenadeLauncherA_Ammo'"));
	if (tempGrenade.Succeeded())
    {
	    grenadeComp->SetStaticMesh(tempGrenade.Object);
    }
	grenadeComp->SetRelativeScale3D(FVector(3.f));

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	ArmRifle();

	// 위젯
	crossZoomUI = CreateWidget(GetWorld(), crossZoomFactory);
	crossHitUI = CreateWidget(GetWorld(), crossHitFactory);
	crossIdleUI = CreateWidget(GetWorld(), crossIdleFactory);
	crossIdleUI->AddToViewport();
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 월드기준 dir를 플레이어기준 dir로 변화하기 위해 플레이어 rotaion을 트랜스폼으로 만듬
//	FTransform playerTrans = GetControlRotation();
	FTransform playerTrans(GetControlRotation());
	// 플레이어 트랜스폼에 맞게 dir 변환
	FVector newDir = playerTrans.TransformVector(dir);
	// Z값 제거 (바닥정지안하게)
	newDir.Z = 0;
	newDir.Normalize();
	// 변환된 dir로 이동 (속도는 self에)
	AddMovementInput(newDir);
	
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyPlayer::InputAxisLookUp);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &AMyPlayer::InputAxisTurnRight);
	PlayerInputComponent->BindAxis(TEXT("MoveVertical"), this, &AMyPlayer::InputAxisMoveVertical);
	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &AMyPlayer::InputAxisMoveHorizontal);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyPlayer::InputActionJump);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPlayer::InputActionFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AMyPlayer::InputActionFireReleased);
	PlayerInputComponent->BindAction(TEXT("Rifle"), IE_Pressed, this, &AMyPlayer::ArmRifle);
	PlayerInputComponent->BindAction(TEXT("RocketLauncher"), IE_Pressed, this, &AMyPlayer::ArmRocketLauncher);
	PlayerInputComponent->BindAction(TEXT("Knife"), IE_Pressed, this, &AMyPlayer::ArmKnife);
	PlayerInputComponent->BindAction(TEXT("Grenade"), IE_Pressed, this, &AMyPlayer::ArmGrenade);
	PlayerInputComponent->BindAction(TEXT("Zoom"), IE_Pressed, this, &AMyPlayer::Zoom);
	PlayerInputComponent->BindAction(TEXT("Zoom"), IE_Released, this, &AMyPlayer::ZoomOut);
}

void AMyPlayer::InputAxisLookUp(float value)
{
	AddControllerPitchInput(value);
}

void AMyPlayer::InputAxisTurnRight(float value)
{
	AddControllerYawInput(value);
}

void AMyPlayer::InputAxisMoveVertical(float value)
{
	dir.X = value;
}

void AMyPlayer::InputAxisMoveHorizontal(float value)
{
	dir.Y = value;
}

void AMyPlayer::InputActionJump()
{
	Jump();
}

void AMyPlayer::InputActionFire()
{
	switch (nowWeapon)
	{
	case WeaponList::Rifle:
		GetWorldTimerManager().SetTimer(rifleTimerhandle, this, &AMyPlayer::FireRifle, fireRifleInterval, true);
		FireRifle();
		break;
	case WeaponList::RocketLauncher:
		FireRocketLauncher();
		break;
	case WeaponList::Knife:
		FireKnife();
		break;
	case WeaponList::Grenade:
		FireGrenade();
		break;
	default:
		break;
	}
}

void AMyPlayer::InputActionFireReleased()
{
	GetWorldTimerManager().ClearTimer(rifleTimerhandle);
}

void AMyPlayer::ArmRifle()
{
	ChangeWeapon(WeaponList::Rifle);
}

void AMyPlayer::ArmRocketLauncher()
{
	ChangeWeapon(WeaponList::RocketLauncher);
}

void AMyPlayer::ArmKnife()
{
	ChangeWeapon(WeaponList::Knife);
}

void AMyPlayer::ArmGrenade()
{
	ChangeWeapon(WeaponList::Grenade);
}

void AMyPlayer::ChangeWeapon(WeaponList value)
{
	switch (value)
	{
	case
		WeaponList::Rifle:
			nowWeapon = value;
			rifleComp->SetVisibility(true);
			rocketLauncherComp->SetVisibility(false);
			grenadeComp->SetVisibility(false);
		break;
	case 
		WeaponList::RocketLauncher:
			nowWeapon = value;
			rifleComp->SetVisibility(false);
			rocketLauncherComp->SetVisibility(true);
			grenadeComp->SetVisibility(false);
		break;
	case
		WeaponList::Knife:
			if (nowWeapon == WeaponList::Rifle || nowWeapon == WeaponList::RocketLauncher)
			{
				crossZoomUI->RemoveFromParent();
				crossIdleUI->AddToViewport();
				playerCamera->SetFieldOfView(90);
			}
			nowWeapon = value;
			UE_LOG(LogTemp, Warning, TEXT("3"));
		break;
	case
		WeaponList::Grenade:
			if (nowWeapon == WeaponList::Rifle || nowWeapon == WeaponList::RocketLauncher)
			{
				crossZoomUI->RemoveFromParent();
				crossIdleUI->AddToViewport();
				playerCamera->SetFieldOfView(90.f);
			}
			nowWeapon = value;
			rifleComp->SetVisibility(false);
			rocketLauncherComp->SetVisibility(false);
			grenadeComp->SetVisibility(true);
		break;
	default:
		break;
	}
}

void AMyPlayer::FireRifle()
{
	// 라인트레이스
	FHitResult hitInfo;
	FVector startLoc = playerCamera->GetComponentLocation();
	FVector endLoc = startLoc + playerCamera->GetForwardVector() * 100000.f;
	FCollisionQueryParams param;
	bool isHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility, param);
	if (isHit)
	{
		FTransform trans(hitInfo.ImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, trans);
		// 적 데미지
		AEnemy* enemy = Cast<AEnemy>(hitInfo.GetActor());
		if (enemy)
		{
			UEnemyFSM* enemyfsm = Cast<UEnemyFSM>(enemy->fsm);
			if (enemyfsm)
			{
				enemyfsm->OnDamageProcess(1);
				CrossHit();
 			}
		}
	}
	// 반동
	AddControllerPitchInput(-0.1f);
	AddControllerYawInput(FMath::RandRange(-0.05f, 0.05f));
	// 총구 화염 이펙트
	UGameplayStatics::SpawnEmitterAttached(rifleMuzzleFire, rifleComp, FName("MuzzleFlash"));
}

void AMyPlayer::FireRocketLauncher()
{
	FVector rocketLoc = rocketLauncherComp->GetSocketLocation(TEXT("FirePosition"));
	GetWorld()->SpawnActor<ARocketAmmo>(rocketFactory, rocketLoc, GetControlRotation());
	// 발사시 화염 이펙트
	UGameplayStatics::SpawnEmitterAttached(rocketMuzzleFront, rocketLauncherComp, FName("MuzzleFlash"));
	UGameplayStatics::SpawnEmitterAttached(rocketMuzzleBack, rocketLauncherComp, FName("MuzzleFlashRear"));
}

void AMyPlayer::FireKnife()
{
	UE_LOG(LogTemp, Warning, TEXT("knife attack"));
}

void AMyPlayer::FireGrenade()
{
//	UE_LOG(LogTemp, Warning, TEXT("grenade attack"));
	GetWorld()->SpawnActor<AGrenade>(grenadeFactory, GetActorLocation()+FVector(0, 0, 120.f), GetControlRotation());

}

void AMyPlayer::Zoom()
{
	switch (nowWeapon)
	{
	case WeaponList::Rifle:
		crossIdleUI->RemoveFromParent();
		crossZoomUI->AddToViewport();
		playerCamera->SetFieldOfView(60.f);
		break;
	case WeaponList::RocketLauncher:
		crossIdleUI->RemoveFromParent();
		crossZoomUI->AddToViewport();
		playerCamera->SetFieldOfView(60.f);
		break;
	case WeaponList::Knife:
		break;
	case WeaponList::Grenade:
		UGameplayStatics::PredictProjectilePath()
		break;
	default:
		break;
	}
}

void AMyPlayer::ZoomOut()
{
	switch (nowWeapon)
	{
	case WeaponList::Rifle:
		crossZoomUI->RemoveFromParent();
		crossIdleUI->AddToViewport();
		playerCamera->SetFieldOfView(90.f);
		break;
	case WeaponList::RocketLauncher:
		crossZoomUI->RemoveFromParent();
		crossIdleUI->AddToViewport();
		playerCamera->SetFieldOfView(90.f);
	case WeaponList::Knife:
		break;
	case WeaponList::Grenade:
		break;
	default:
		break;
	}
}

void AMyPlayer::CrossHit()
{
	if (!bisHitUIOn)
	{
		bisHitUIOn = true;
		crossHitUI->AddToViewport();
		FTimerHandle crossHitTimerhandle;
		GetWorld()->GetTimerManager().SetTimer(crossHitTimerhandle, FTimerDelegate::CreateLambda([&]()
			{
				crossHitUI->RemoveFromParent();
				bisHitUIOn = false;
			}), 1.f, false);
	}
}

void AMyPlayer::SetPlayerHP(int hp)
{
	playerHP = hp;
}

int AMyPlayer::GetPlayerHP()
{
	return playerHP;
}

