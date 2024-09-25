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
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY( EditAnywhere, Category = "AI" )
	UBehaviorTree* BehaviorTree;
};
