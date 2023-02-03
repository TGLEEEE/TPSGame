// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerAnim.h"
#include "MyPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>

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
		bisFalling = player->GetCharacterMovement()->IsFalling();
	}
}

void UMyPlayerAnim::AnimNotify_Get()
{
	if (player)
	{
		player->grenadeComp->SetVisibility(true);
		player->bIsGrenadeAiming = true;
	}
}

void UMyPlayerAnim::AnimNotify_Throw()
{
	if (player)
	{
		player->grenadeComp->SetVisibility(false);
		player->FireGrenade();
		player->bIsGrenadeAiming = false;
	}
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
