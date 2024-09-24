// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterAIContoller.h"

#include "Kismet/GameplayStatics.h"

void AShooterCharacterAIContoller::TickTick(float DeltaTime)
{
	Super::Tick( DeltaTime );

	APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn( this, 0 );
	if (PlayerPawn && LineOfSightTo( PlayerPawn ))
	{
		SetFocus( PlayerPawn );
		MoveToActor( PlayerPawn , AcceptanceRadius);
	}
	else
	{
		ClearFocus( EAIFocusPriority::Default );
		StopMovement();
	}
}

void AShooterCharacterAIContoller::BeginPlay()
{
	Super::BeginPlay();
	
}
