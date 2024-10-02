// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded( EndGameFocus, bIsWinner );

	// restart the level after a delay
	GetWorldTimerManager().SetTimer( RestartTimer, this, &APlayerController::RestartLevel, RestartDelay );
}
