// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

private:
	UPROPERTY( VisibleAnywhere )
	USceneComponent* Root;

	UPROPERTY( VisibleAnywhere )
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY( EditAnywhere, Category = "Combat", meta = (ClampMin = "1.0") )
	float Range = 100.0f;

	UPROPERTY( EditAnywhere, Category = "Combat", meta = (ClampMin = "1.0") )
	float HitRadius = 1.0f;

	UPROPERTY( EditAnywhere, Category = "Combat", meta = (ClampMin = "0.01") )
	float Damage = 1.0f;

	UPROPERTY( EditAnywhere, Category = "Combat" )
	UParticleSystem* MuzzleFlash;

	UPROPERTY( EditAnywhere, Category = "Combat" )
	UParticleSystem* HitParticle;

	bool GunTrace(FHitResult &HitResult, FVector &ShotDirection) const;
	AController* GetController() const;
	
};
