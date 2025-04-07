// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupAbleObject.h"
#include "Deathbox.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API ADeathbox : public APickupAbleObject
{
	GENERATED_BODY()


public:
	//Despite not collecting anything, using collect item code as a generic "On collision" function.
	virtual void CollectItem() override;
	
};
