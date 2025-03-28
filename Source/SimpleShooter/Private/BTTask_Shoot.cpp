// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT( "Shoot" );
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if ( Super::ExecuteTask( OwnerComp, NodeMemory ) == EBTNodeResult::Failed )
	{
		return EBTNodeResult::Failed;
	}

	AAIController const* Owner = OwnerComp.GetAIOwner();
	if ( !Owner )
	{
		return EBTNodeResult::Failed;
	}

	AShooterCharacter* Character = Cast< AShooterCharacter >( Owner->GetPawn() );
	if ( !Character )
	{
		return EBTNodeResult::Failed;
	}

	Character->FireGun();

	return EBTNodeResult::Succeeded;
}
