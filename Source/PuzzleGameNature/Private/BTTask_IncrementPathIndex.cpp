// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncrementPathIndex.h"

#include "Bear_AIController.h"
#include "BearAI.h"
#include "BearAI_PatrolPath.h"
#include "BehaviorTree/BlackboardComponent.h"

// Constructor Definition
UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer) :
	UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Increment Path Index");
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//try and get the BearAI Controller
	if (auto* const Cont = Cast<ABear_AIController>(OwnerComp.GetAIOwner()))
	{
		//try and get the npc
		if (auto* const npc = Cast<ABearAI>(Cont->GetPawn()))
		{
			//try and get the blackboard
			if (auto* const bc = OwnerComp.GetBlackboardComponent())
			{
				//get number of patrol points and min/max number of index
				auto const NumberOfPoints = npc->GetBearAI_PatrolPath()->Num();
				auto const MinimumIndex = 0;
				auto const MaximumIndex = NumberOfPoints - 1;
				auto Index = bc->GetValueAsInt(GetSelectedBlackboardKey());

				//change direction if we are on the first or last index, in bidirectional mode.
				if (bBiDirectional)
				{
					if (Index >= MaximumIndex && Direction == EDirectionType::Forward)
					{
						Direction = EDirectionType::Reverse;
					}
					else if (Index == MinimumIndex && Direction == EDirectionType::Reverse)
					{
						Direction = EDirectionType::Forward;
					}
				}

				//write new value of index to blackboard
				bc->SetValueAsInt(GetSelectedBlackboardKey(),
					(Direction == EDirectionType::Forward ? ++Index : --Index) % NumberOfPoints);

				//finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}

	}
	return EBTNodeResult::Failed;
}
