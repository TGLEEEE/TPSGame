// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerAnim.h"
#include "MyPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>

void UMyPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyPlayer* player = Cast<AMyPlayer>(TryGetPawnOwner());
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
	AMyPlayer* player = Cast<AMyPlayer>(TryGetPawnOwner());
	if (player)
	{
		player->grenadeComp->SetVisibility(true);
	}
}

void UMyPlayerAnim::AnimNotify_Throw()
{
	AMyPlayer* player = Cast<AMyPlayer>(TryGetPawnOwner());
	if (player)
	{
		player->grenadeComp->SetVisibility(false);
		player->FireGrenade();
	}
}

void UMyPlayerAnim::FireAnim()
{
	Montage_Play(fireAnimMontage);
}

void UMyPlayerAnim::PlayGrenadeAnim(FName sectionName)
{
	AMyPlayer* player = Cast<AMyPlayer>(TryGetPawnOwner());
	if (player)
	{
		player->PlayAnimMontage(grenadeAnimMontage, 2.f, sectionName);
	}
}
