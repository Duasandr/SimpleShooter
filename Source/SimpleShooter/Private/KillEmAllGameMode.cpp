// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "ShooterCharacter.h"
#include "ShooterCharacterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled( PawnKilled );

	APlayerController* PlayerController = Cast< APlayerController >( PawnKilled->GetController() );
	if ( PlayerController )
	{
		// player died
		EndGame( false );
	}
	else
	{
		// ai controller died

		// check for the win condition (all AI controlled characters are dead) 
		for ( AShooterCharacterAIController* Controller : TActorRange< AShooterCharacterAIController >( GetWorld() ) )
		{
			AShooterCharacter const* Character = Cast< AShooterCharacter >( Controller->GetPawn() );
			if ( Character && !Character->IsDead() )
			{
				// at least an AI character is alive
				return;
			}
		}
		// all the AI characters are dead
		EndGame( true );
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
