// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupAbleObject.h"
#include "NextCameraCollision.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API ANextCameraCollision : public APickupAbleObject
{
	GENERATED_BODY()
	
public:
	virtual void CollectItem() override;
};
