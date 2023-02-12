// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElectricTrap.generated.h"

UCLASS()
class TPSGAME_API AElectricTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElectricTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	//UFUNCTION(BlueprintCallable)
		//void InElectricTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& /SweepResult);

	//UFUNCTION(BlueprintCallable)
	//	void OutElectricTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	float currentTime = 0;
	float shockTime = 3.f;

public:

	// 전기공장
	//UPROPERTY(EditAnywhere)
		//class UParticleSystem* bulletElectricFactory;

	UPROPERTY(EditAnywhere)
		class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* meshComp;
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* particleComp;

	class AEnemy* enemy;
	FTimerHandle moveHandle;


};
