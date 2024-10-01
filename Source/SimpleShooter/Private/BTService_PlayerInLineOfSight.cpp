// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerInLineOfSight.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerInLineOfSight::UBTService_PlayerInLineOfSight()
{
	NodeName = TEXT( "Player In Line Of Sight" );
}

void UBTService_PlayerInLineOfSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );

	APawn const* Pawn = UGameplayStatics::GetPlayerPawn( this, 0 );
	AAIController const* Controller = OwnerComp.GetAIOwner();
	if ( !( Pawn && Controller ) )
	{
		return;
	}

	FName const SelectedKey = GetSelectedBlackboardKey();
	if ( Controller->LineOfSightTo( Pawn ) )
	{
		FVector const PawnLocation = Pawn->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector( SelectedKey, PawnLocation );
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue( SelectedKey );
	}
}
