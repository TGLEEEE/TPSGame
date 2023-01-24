// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "RocketAmmo.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Player/character.character'"));
	if (mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(mesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	playerSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("playerSpringArm"));
	playerSpringArm->SetupAttachment(RootComponent);
	playerSpringArm->TargetArmLength = 250;
	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("playerCamera"));
	playerCamera->SetupAttachment(playerSpringArm);
	playerCamera->SetRelativeLocation(FVector(0, 50, 100));

	bUseControllerRotationYaw = true;
	playerSpringArm->bUsePawnControlRotation = true;
	playerCamera->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	rocketLauncherComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Rocket Launcher Mesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempRocketLauncher(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Weapon/MilitaryWeapSilver/Weapons/Rocket_Launcher_A.Rocket_Launcher_A'"));
	if (tempRocketLauncher.Succeeded())
	{
		rocketLauncherComp->SetSkeletalMesh(tempRocketLauncher.Object);
	}
	rocketLauncherComp->SetupAttachment(GetMesh());
	rocketLauncherComp->SetRelativeLocation(FVector(-30, 0, 120));

	rifleComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Rifle Mesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempRifle(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Weapon/MilitaryWeapSilver/Weapons/Assault_Rifle_A.Assault_Rifle_A'"));
	if (tempRifle.Succeeded())
	{
		rifleComp->SetSkeletalMesh(tempRifle.Object);
	}
	rifleComp->SetupAttachment(GetMesh());
	rifleComp->SetRelativeLocation(FVector(-30, 0, 120));
	
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	ArmRifle();
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
	
	// 라인트레이스
	startLoc = playerCamera->GetComponentLocation();
	endLoc = startLoc + playerCamera->GetForwardVector() * 100000.f;
	isHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_Visibility, param);
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
		break;
	case 
		WeaponList::RocketLauncher:
			nowWeapon = value;
			rifleComp->SetVisibility(false);
			rocketLauncherComp->SetVisibility(true);
		break;
	case
		WeaponList::Knife:
			nowWeapon = value;
			UE_LOG(LogTemp, Warning, TEXT("3"));
		break;
	case
		WeaponList::Grenade:
			nowWeapon = value;
			UE_LOG(LogTemp, Warning, TEXT("4"));
		break;
	default:
		break;
	}
}

void AMyPlayer::FireRifle()
{
	// 라이플 총알 이펙트
	if (isHit)
	{
		FTransform trans(hitInfo.ImpactPoint);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, trans);
	}
	// 반동
	AddControllerPitchInput(-0.1f);
	AddControllerYawInput(FMath::RandRange(-0.05f, 0.05f));
}

void AMyPlayer::FireRocketLauncher()
{
	FVector rocketLoc = rocketLauncherComp->GetSocketLocation(TEXT("FirePosition"));
	GetWorld()->SpawnActor<ARocketAmmo>(rocketFactory, rocketLoc, GetControlRotation());
}

void AMyPlayer::FireKnife()
{
	UE_LOG(LogTemp, Warning, TEXT("knife attack"));
}

void AMyPlayer::FireGrenade()
{
	UE_LOG(LogTemp, Warning, TEXT("grenade attack"));
}

