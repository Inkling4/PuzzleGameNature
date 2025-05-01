// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"

#include "CombatInterface.h"
#include "Bear_AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//If we are out of range, do not attack the player
	auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange)
	{
		//Finish Task
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	//We are in range so get the Bear_AIController and BearAI
	auto const* const cont = OwnerComp.GetAIOwner();
	auto* const npc = Cast<ABearAI>(cont->GetPawn());

	//If BearAI supports the ICombatInterface, cast and call the Execute_MeleeAttack function
	if (auto* const icombat = Cast<ICombatInterface>(npc))
	{
		//necessary check to see if montage is done so we don't replay it.
		if (MontageHasFinished(npc))
		{
			icombat->Execute_MeleeAttack(npc);
			npc->MeleeAttack();
		}
	}

	//Finish Task
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Type();
}

bool UBTTask_MeleeAttack::MontageHasFinished(ABearAI* const npc)
{
	return npc->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npc->GetMontage());
}

