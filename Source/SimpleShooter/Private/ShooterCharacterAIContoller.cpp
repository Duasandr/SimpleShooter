// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterAIContoller.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterCharacterAIContoller::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

	// if ( PlayerPawn && LineOfSightTo( PlayerPawn ) )
	// {
	// 	SetFocus( PlayerPawn );
	// 	MoveToActor( PlayerPawn, AcceptanceRadius );
	// }
	// else
	// {
	// 	ClearFocus( EAIFocusPriority::Default );
	// 	StopMovement();
	// }
}

void AShooterCharacterAIContoller::BeginPlay()
{
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( this, 0 );
	APawn* ControlledPawn = GetPawn();

	if ( BehaviorTree && PlayerPawn && ControlledPawn )
	{
		RunBehaviorTree( BehaviorTree );
		GetBlackboardComponent()->SetValueAsVector( TEXT( "StartLocation" ), ControlledPawn->GetActorLocation() );
		GetBlackboardComponent()->SetValueAsVector( TEXT( "PlayerLocation" ), PlayerPawn->GetActorLocation() );
	}
}
