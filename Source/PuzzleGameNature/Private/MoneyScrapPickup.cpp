// Fill out your copyright notice in the Description page of Project Settings.


#include "MoneyScrapPickup.h"

//Sets default values
AMoneyScrapPickup::AMoneyScrapPickup()
{
	ScrapValue = 1;
}


void AMoneyScrapPickup::CollectItem()
{
	Super::CollectItem();

	ProtagonistRef->CollectMoneyScrap(ScrapValue);
	Destroy();
}
