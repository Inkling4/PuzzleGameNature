 // Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPathPoint.h"

#include "Bear_AIController.h"
#include "BearAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& ObjectInitializer) :
	UBTTask_BlackboardBase{ ObjectInitializer }
{
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	//attempt to get the npc's controller
	if (auto* const cont = Cast<ABear_AIController>(OwnerComp.GetAIOwner()))
	{
		//attempt to get the blackboard component from the behavior tree
		if (auto* const bc = OwnerComp.GetBlackboardComponent())
		{
			//get the current patrol index from the blackboard
			auto const Index = bc->GetValueAsInt(GetSelectedBlackboardKey());	

			//get the npc
			if (auto* npc = Cast<ABearAI>(cont->GetPawn()))
			{
				//get the current patrol path vector from the npc
				auto const Point = npc->GetBearAI_PatrolPath()->GetPatrolPoint(Index);

				//convert the local vector to a global point
				auto const GlobalPoint = npc->GetBearAI_PatrolPath()->GetActorTransform().TransformPosition(Point);
				bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

				//finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}

		}
	}
	return EBTNodeResult::Failed;
}
