// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInMeleeRange.h"
#include "Bear_AIController.h"
#include "BearAI.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_IsPlayerInMeleeRange::UBTService_IsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Melee Range");
}

void UBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Bear_AIController and BearAI
	auto const* const cont = Cast<ABear_AIController>(OwnerComp.GetAIOwner());
	auto const* const npc = Cast<ABearAI>(cont->GetPawn());

	//Get Player Character
	auto const* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//Write true or false to the blackboard key depending on whether the player is in range
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(
		GetSelectedBlackboardKey(),
		npc->GetDistanceTo(player) <= MeleeRange);
}
