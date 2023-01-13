// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "RocketAmmo.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/player/character.character'"));
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

	skMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>rocketLauncher(TEXT("/Script/Engine.SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Rocket_Launcher_A.Rocket_Launcher_A'"));
	if (rocketLauncher.Succeeded())
	{
		skMeshComp->SetSkeletalMesh(rocketLauncher.Object);
	}
	skMeshComp->SetupAttachment(GetMesh());
	skMeshComp->SetRelativeLocation(FVector(-30, 0, 120));
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyPlayer::InputActionJump);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPlayer::InputActionFire);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyPlayer::InputAxisLookUp);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &AMyPlayer::InputAxisTurnRight);
	PlayerInputComponent->BindAxis(TEXT("MoveVertical"), this, &AMyPlayer::InputAxisMoveVertical);
	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &AMyPlayer::InputAxisMoveHorizontal);
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
	FTransform rocketTrans = skMeshComp->GetSocketTransform(TEXT("FirePosition"));
	GetWorld()->SpawnActor<ARocketAmmo>(BulletFactory, rocketTrans);
}

