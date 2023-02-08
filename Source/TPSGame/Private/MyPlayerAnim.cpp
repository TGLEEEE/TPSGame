// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerAnim.h"
#include "MyPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/GameplayStatics.h>

void UMyPlayerAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	player = Cast<AMyPlayer>(TryGetPawnOwner());
}

void UMyPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (player)
	{
		FVector vel = player->GetVelocity();
		forwardVel = FVector::DotProduct(vel, player->GetActorForwardVector());
		rightVel = FVector::DotProduct(vel, player->GetActorRightVector());
		bIsFalling = player->GetCharacterMovement()->IsFalling();
	}
}

void UMyPlayerAnim::AnimNotify_Get()
{
	if (player)
	{
		player->grenadeComp->SetVisibility(true);
		player->bIsGrenadeAiming = true;
		UGameplayStatics::PlaySound2D(this, player->grenadeSetSound);
	}
}

void UMyPlayerAnim::AnimNotify_Throw()
{
	if (player)
	{
		player->grenadeComp->SetVisibility(false);
		player->FireGrenade();
		player->bIsGrenadeAiming = false;
		UGameplayStatics::PlaySound2D(GetWorld(), player->grenadeGoSound);
	}
}

void UMyPlayerAnim::AnimNotify_FirstAttackEnd()
{
	if (player->bIsKnifeAttackPressing)
	{
		PlayKnifeAttackAnim(TEXT("SecondAttack"));
	}
	else
	{
		player->knifeComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		player->GetCharacterMovement()->MaxWalkSpeed = 400;
	}
}

void UMyPlayerAnim::AnimNotify_SecondAttackEnd()
{
	player->knifeComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	player->GetCharacterMovement()->MaxWalkSpeed = 400;
	GetWorld()->SpawnActor<AActor>(player->knifeEffect, player->knifeComp->GetComponentLocation(), FRotator::ZeroRotator);
	UGameplayStatics::PlaySound2D(this, player->spadeSound, 2.f);
}

void UMyPlayerAnim::FireAnim()
{
	Montage_Play(fireAnimMontage);
}

void UMyPlayerAnim::PlayGrenadeAnim(FName sectionName)
{
	if (player)
	{
		player->PlayAnimMontage(grenadeAnimMontage, 2.f, sectionName);
	}
}

void UMyPlayerAnim::PlayKnifeAttackAnim(FName sectionName)
{
	if (player)
	{
		player->PlayAnimMontage(knifeAnimMontage, 1.2f, sectionName);
	}
}
