// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EV_Door.generated.h"

UCLASS()
class TPSGAME_API AEV_Door : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEV_Door();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* doorLeft;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* doorRight;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	void moveLeftDoor(FVector start, FVector end);
	void moveRightDoor(FVector start, FVector end);

	bool bDoOpen;
	bool bDoClose;
	bool bOpenRightDelay;
	bool bDoOnce;

	float timeL = 0;
	float timeR = 0;

	FVector startLocLeft;
	FVector endLocLeft;
	FVector startLocRight;
	FVector endLocRight;


};
