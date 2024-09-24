// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterCharacterAIContoller.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterCharacterAIContoller : public AAIController
{
	GENERATED_BODY()

public: 
	void TickTick(float DeltaTime);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	// acceptance radius is the distance the AI controller stops before reaching the actor
	float AcceptanceRadius = 100.0f;
};
