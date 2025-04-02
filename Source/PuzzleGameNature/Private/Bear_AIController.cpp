// Fill out your copyright notice in the Description page of Project Settings.


#include "Bear_AIController.h"
#include "BearAI.h"


ABear_AIController::ABear_AIController(FObjectInitializer const& ObjectInitializer)
{
}

void ABear_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ABearAI* const BearAI = Cast<ABearAI>(InPawn))
	{
		if (UBehaviorTree* const tree = BearAI->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
