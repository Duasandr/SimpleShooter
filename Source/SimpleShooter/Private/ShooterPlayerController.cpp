// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded( EndGameFocus, bIsWinner );

	// display lose widget
	UUserWidget* LoseScreenWidget = CreateWidget( this, LoseScreenWidgetClass );
	if ( LoseScreenWidget )
	{
		LoseScreenWidget->AddToViewport();
	}

	// restart the level after a delay
	GetWorldTimerManager().SetTimer( RestartTimer, this, &APlayerController::RestartLevel, RestartDelay );
}
