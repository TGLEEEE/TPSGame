// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RocketExplosion.generated.h"

UCLASS()
class TPSGAME_API ARocketExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARocketExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	class URadialForceComponent* radialForceComp;
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* sphereComp;
	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent* particleComp;
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void SelfDestroy();
	FTimerHandle destroyTimer;
};
