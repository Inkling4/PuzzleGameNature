// Fill out your copyright notice in the Description page of Project Settings.


#include "Bear_AIController.h"
#include "BearAI.h"
#include "Protagonist.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


ABear_AIController::ABear_AIController(FObjectInitializer const& ObjectInitializer)
{
	SetupPerceptionSystem();
}

// If the pawn is the npc and the cast succeeds, we attempt to get the Behavior tree
void ABear_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ABearAI* const npc = Cast<ABearAI>(InPawn))
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree())
		{
			// b as local variable
			UBlackboardComponent* b;
			// function is then called to try and get the blackboard asset from the tree and puts in b parameter
			UseBlackboard(tree->BlackboardAsset, b);
			// Sets the blackboard to the b parameter
			Blackboard = b;
			// Attempts to run the behavior tree
			RunBehaviorTree(tree);
		}
	}
}

void ABear_AIController::SetupPerceptionSystem()
{
	// Creates sight perception system 
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		// Creates Perception Component if SightConfig isn't null
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(
			TEXT("Perception Component")));
		SightConfig->SightRadius = 1000.0f; // If player is within this radius, they will be seen
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 100.f; // Radius where npc will stop seeing the player
		SightConfig->PeripheralVisionAngleDegrees = 90.f; // npc field of view. 90 degrees means npc can only see in front
		SightConfig->SetMaxAge(5.f); // time in seconds when the player detection completely decays, npc forgetting the player
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f; // Range from the player to the last seen location of the npc. If player is within this range, npc keeps chasing

		// npc detects everyone in sight if they exist within the npc's sight
		SightConfig->DetectionByAffiliation.bDetectEnemies = true; 
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		// Sets the dominant sense by getting the sense implementation from the SightConfig
		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		// OnTargetDetected called when something is sensed
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ABear_AIController::OnTargetDetected);
		// Configure sense system with the SightConfig
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void ABear_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	// Attempts to cast actor to the protagonist character class and tests if the actor is the player
	if (auto* const ch = Cast<AProtagonist>(Actor))
	{
		// If the actor is the player, then we get the blackboard component, and identifies whether the player is successfully sensed.
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}

