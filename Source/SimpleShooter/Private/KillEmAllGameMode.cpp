// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled( PawnKilled );
	APlayerController* PlayerController = Cast< APlayerController >( PawnKilled->GetController() );
	if ( PlayerController )
	{
		// player died
		EndGame( false );
	}
}

void AKillEmAllGameMode::EndGame(bool const bIsPlayerWinner) const
{
	for ( AController* Controller : TActorRange< AController >( GetWorld() ) )
	{
		bool const bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded( Controller->GetPawn(), bIsWinner );
	}
}
