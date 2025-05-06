// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Bear_AIController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API ABear_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	// An explicit constructor that takes in one parameter
	explicit ABear_AIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	// Configuration that sets up the perception system
	class UAISenseConfig_Sight* SightConfig;

	// Function that sets up the perception system
	void SetupPerceptionSystem();

	// Function that will be attached to a delegate, hence why we use UFUNCTION
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);
};
