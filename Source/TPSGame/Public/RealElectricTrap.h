// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RealElectricTrap.generated.h"

UCLASS()
class TPSGAME_API ARealElectricTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARealElectricTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = ElectricSetting)
	TSubclassOf <class AElectricTrap> electricFactory;

	UPROPERTY(EditAnywhere, Category = ElectricSetting)
		class UArrowComponent* arrow;

	UFUNCTION(BlueprintCallable)
	void InRealElectricTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	float currentTime = 0;
	float shockTime = 3;
	class AEnemy* enemy;
	FTimerHandle moveHandle;


};
