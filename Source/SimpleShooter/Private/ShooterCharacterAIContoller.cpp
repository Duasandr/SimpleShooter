// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterAIContoller.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterCharacterAIContoller::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( this, 0 );

	if ( PlayerPawn && LineOfSightTo( PlayerPawn ) )
	{
		GetBlackboardComponent()->SetValueAsVector( TEXT( "PlayerLocation" ), PlayerPawn->GetActorLocation() );
		GetBlackboardComponent()->SetValueAsVector( TEXT( "PlayerLastKnownLocation" ), PlayerPawn->GetActorLocation() );
	}
	else
	{
		GetBlackboardComponent()->ClearValue( TEXT( "PlayerLocation" ) );
	}
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
