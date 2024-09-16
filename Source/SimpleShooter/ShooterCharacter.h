// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY( EditDefaultsOnly, Category = "Enhanced Input" )
	class UInputMappingContext* InputMappingContext;

	UPROPERTY( EditDefaultsOnly, Category = "Enhanced Input|Movement" )
	class UInputAction* MoveAction;

	UPROPERTY( EditDefaultsOnly, Category = "Enhanced Input|Movement" )
	UInputAction* LookAction;

	UPROPERTY( EditDefaultsOnly, Category = "Enhanced Input|Movement" )
	UInputAction* JumpAction;

	void Move(struct FInputActionValue const& ActionValue);
	void Look		(FInputActionValue const& ActionValue);
};
