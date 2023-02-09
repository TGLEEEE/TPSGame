// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grenade.generated.h"

UCLASS()
class TPSGAME_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* grenadeComp;
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* projectileComp;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGrenadeExplosion> explosion;
	void SelfExplosion();
	UPROPERTY(EditDefaultsOnly)
	USoundBase* grenadeWarningSound;
};
