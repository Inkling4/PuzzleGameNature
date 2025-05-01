// Fill out your copyright notice in the Description page of Project Settings.


#include "CrowbarPickup.h"





void ACrowbarPickup::CollectItem()
{
	Super::CollectItem();
	ProtagonistRef->CollectCrowbar();
	OnCrowbarPickup();
	Destroy();
}

void ACrowbarPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}
