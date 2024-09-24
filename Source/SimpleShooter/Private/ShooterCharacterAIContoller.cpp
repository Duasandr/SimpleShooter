// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterAIContoller.h"

#include "Kismet/GameplayStatics.h"

void AShooterCharacterAIContoller::BeginPlay()
{
	Super::BeginPlay();
	APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn( this, 0 );
	if (PlayerPawn)
	{
		SetFocus( PlayerPawn );

		// acceptance radius is the distance the AI controller stops before reaching the actor
		constexpr float AcceptanceRadius = 100.0f;
		MoveToActor( PlayerPawn , AcceptanceRadius);
	}
}
