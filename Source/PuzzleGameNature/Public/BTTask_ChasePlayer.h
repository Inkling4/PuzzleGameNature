// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API UBTTask_ChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	// constructor for the Behavior tree task, and the execute task function
	explicit UBTTask_ChasePlayer(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
