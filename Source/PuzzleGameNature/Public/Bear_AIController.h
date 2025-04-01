// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Bear_AIController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API ABear_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	explicit ABear_AIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
