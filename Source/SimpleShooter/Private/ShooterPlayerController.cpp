// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget( this, HUDClass );
	if ( HUD )
	{
		HUD->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded( EndGameFocus, bIsWinner );

	UUserWidget* EndScreenWidget;
	if ( bIsWinner )
	{
		EndScreenWidget = CreateWidget( this, WinScreenWidgetClass );
	}
	else
	{
		EndScreenWidget = CreateWidget( this, LoseScreenWidgetClass );
	}

	HUD->RemoveFromParent();

	EndScreenWidget->AddToViewport();

	// restart the level after a delay
	GetWorldTimerManager().SetTimer( RestartTimer, this, &APlayerController::RestartLevel, RestartDelay );
}
