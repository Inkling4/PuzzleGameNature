// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "NextLevelInteract.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API ANextLevelInteract : public AInteractableObject
{
	GENERATED_BODY()

public:
	virtual void Interact() override;
	//Called on interact
	UFUNCTION(BlueprintImplementableEvent)
	void NextLevel();
	FText 
};
