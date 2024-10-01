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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION( BlueprintPure )
	FORCEINLINE bool IsDead() const { return Health <= 0.0f; }

	void FireGun();

private:
	UPROPERTY( EditDefaultsOnly, Category = "Gameplay|Enhanced Input" )
	class UInputMappingContext* InputMappingContext;

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay|Enhanced Input|Actions" )
	class UInputAction* LookAction;

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay|Enhanced Input|Actions" )
	UInputAction* LookRateAction;

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay| Gamepad" )
	FVector2D LookAxisRotationRate = FVector2D::One();

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay|Enhanced Input|Actions" )
	UInputAction* MoveAction;

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay|Enhanced Input|Actions" )
	UInputAction* JumpAction;

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay|Enhanced Input|Actions" )
	UInputAction* FireGunAction;

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay| Combat" )
	TSubclassOf< class AGun > GunClass;

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay|Combat" )
	float MaxHealth = 1.0f;

	UPROPERTY( VisibleAnywhere, Category = "Gameplay|Combat" )
	float Health = 0.0f;

	UPROPERTY()
	AGun* Gun;

	void Move(struct FInputActionValue const& ActionValue);
	void Look(FInputActionValue const& ActionValue);
	/**
	 * Adjusts looking around with the controller by taking into account the frame rate.
	 * @param ActionValue Value passed by enhanced input
	 */
	void LookRate(FInputActionValue const& ActionValue);
};
