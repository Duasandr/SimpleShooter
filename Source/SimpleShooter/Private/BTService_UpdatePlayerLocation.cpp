// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = TEXT( "Update Player Location" );
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );

	APawn const* Pawn = UGameplayStatics::GetPlayerPawn( this, 0 );
	if ( Pawn )
	{
		FVector const PawnLocation = Pawn->GetActorLocation();
		FName const SelectedKey = GetSelectedBlackboardKey();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector( SelectedKey, PawnLocation );
	}
}
