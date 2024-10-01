// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type const Result = Super::ExecuteTask( OwnerComp, NodeMemory );
	
	if ( Result == EBTNodeResult::Succeeded )
	{
		FName const SelectedKey = GetSelectedBlackboardKey();
		OwnerComp.GetBlackboardComponent()->ClearValue( SelectedKey );	
	}
	
	return Result;
}
