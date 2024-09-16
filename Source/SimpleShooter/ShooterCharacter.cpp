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

	if ( APlayerController const* PlayerController = Cast< APlayerController >( Controller ) )
	{
		if ( UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem >( PlayerController->GetLocalPlayer() ) )
		{
			Subsystem->AddMappingContext( InputMappingContext, 0 );
		}
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	UEnhancedInputComponent* EnhancedInputComponent = Cast< UEnhancedInputComponent >( PlayerInputComponent );
	if ( EnhancedInputComponent )
	{
		EnhancedInputComponent->BindAction( MoveAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Move );
		EnhancedInputComponent->BindAction( LookAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Look );
		EnhancedInputComponent->BindAction( JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump );
	}
}

void AShooterCharacter::Move(FInputActionValue const& ActionValue)
{
	FVector2d const MovementVector = ActionValue.Get<FVector2d>();
	if ( Controller )
	{
		// find the right and forward vectors of the controller by using rotation matrices
		FRotator const ControlRotation = Controller->GetControlRotation();
		FRotator const YawRotation = FRotator(0.0, ControlRotation.Yaw, 0.0);
		FVector  const ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis( EAxis::X );
		FVector  const RightDirection	= FRotationMatrix(YawRotation).GetUnitAxis( EAxis::Y );

		AddMovementInput( ForwardDirection, MovementVector.Y );	// move forward/backwards
		AddMovementInput( RightDirection, MovementVector.X );	// move left/right
	}
}

void AShooterCharacter::Look(FInputActionValue const& ActionValue)
{
	FVector2D const LookAxis = ActionValue.Get<FVector2D>();
	if ( Controller )
	{
		AddControllerYawInput( LookAxis.X );	// look left/right
		AddControllerPitchInput( LookAxis.Y );  // look up/down
	}
}
