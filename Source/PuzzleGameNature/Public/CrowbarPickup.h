// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupAbleObject.h"
#include "CrowbarPickup.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API ACrowbarPickup : public APickupAbleObject
{
	GENERATED_BODY()
protected:

public:
	//Sets crowbar to true, and deletes the actor.
	virtual void CollectItem() override;
	virtual void Tick(float DeltaTime) override;
	//Called when the player picks up the crowbar.
	UFUNCTION(BlueprintImplementableEvent, category = "CrowbarPickup")
	void OnCrowbarPickup();
};
