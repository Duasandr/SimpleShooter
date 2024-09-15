// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController const * PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(
		MoveForwardInput,
		ETriggerEvent::Triggered,
		this,
		&AShooterCharacter::MoveForward
		);
	EnhancedInputComponent->BindAction(
		MoveRightInput,
		ETriggerEvent::Triggered,
		this,
		&AShooterCharacter::MoveRight
		);
	EnhancedInputComponent->BindAction(
		LookUpInput,
		ETriggerEvent::Triggered,
		this,
		&AShooterCharacter::LookUp);
	EnhancedInputComponent->BindAction(
		LookRightInput,
		ETriggerEvent::Triggered,
		this,
		&AShooterCharacter::LookRight
		);
}

void AShooterCharacter::MoveForward(FInputActionValue const& ActionValue)
{
	AddMovementInput( GetActorForwardVector() * ActionValue.GetMagnitude() );	
}

void AShooterCharacter::MoveRight(FInputActionValue const& ActionValue)
{
	AddMovementInput( GetActorRightVector() * ActionValue.GetMagnitude() );
}

void AShooterCharacter::LookUp(FInputActionValue const& ActionValue)
{
	AddControllerPitchInput(ActionValue.GetMagnitude());
}

void AShooterCharacter::LookRight(FInputActionValue const& ActionValue)
{
	AddControllerYawInput(ActionValue.GetMagnitude());	
}



