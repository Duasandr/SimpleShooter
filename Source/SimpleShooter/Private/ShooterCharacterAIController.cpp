// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterAIController.h"

#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

bool AShooterCharacterAIController::IsDead() const
{
	AShooterCharacter const* Character = Cast< AShooterCharacter >( GetPawn() );
	if ( Character )
	{
		return Character->IsDead();
	}

	return true;
}

void AShooterCharacterAIController::BeginPlay()
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
