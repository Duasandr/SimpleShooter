// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = TEXT( "Update Player Location" );
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );

	AAIController const* Owner = OwnerComp.GetAIOwner();
	if ( !Owner )
	{
		return;
	}

	APawn const* Pawn = Owner->GetPawn();
	if ( !Pawn )
	{
		return;
	}

	FVector const PawnLocation = Pawn->GetActorLocation();
	FName const SelectedKey = GetSelectedBlackboardKey();
	OwnerComp.GetBlackboardComponent()->SetValueAsVector( SelectedKey, PawnLocation );
}
