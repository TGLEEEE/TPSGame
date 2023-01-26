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
