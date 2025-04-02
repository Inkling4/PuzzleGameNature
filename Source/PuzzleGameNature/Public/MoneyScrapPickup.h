// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupAbleObject.h"
#include "MoneyScrapPickup.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API AMoneyScrapPickup : public APickupAbleObject
{
	GENERATED_BODY()

public:
	AMoneyScrapPickup();
	virtual void CollectItem() override;
	//Amount of scrap this object is worth.
	UPROPERTY(EditAnywhere, category = "Pickup")
	int32 ScrapValue;
};
