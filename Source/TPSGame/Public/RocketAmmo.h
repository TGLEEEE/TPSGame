// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RocketAmmo.generated.h"

UCLASS()
class TPSGAME_API ARocketAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARocketAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

UPROPERTY(EditDefaultsOnly)
class USphereComponent* sphereComp;
UPROPERTY(EditDefaultsOnly)
class UStaticMeshComponent* MeshComp;
UPROPERTY(EditDefaultsOnly)
class UProjectileMovementComponent* projectileComp;

UFUNCTION()
void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
