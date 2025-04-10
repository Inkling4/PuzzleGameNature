// Fill out your copyright notice in the Description page of Project Settings.


#include "MedkitMerchant.h"
#include "Protagonist.h"


AMedkitMerchant::AMedkitMerchant()
{
	//Change this in editor if needed
	MedkitPrice = 3;
}


void AMedkitMerchant::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMedkitMerchant::Interact()
{
	Super::Interact();
	if (ProtagonistRef == nullptr) {return;}
	if (ProtagonistRef->GetMoneyscraps() < MedkitPrice)
	{
		//Called so blueprints can handle animations and cutscenes if you don't have the funds
		InsufficientFunds();
	}
	else
	{
		ProtagonistRef->LoseMoneyScrap(MedkitPrice);
		ProtagonistRef->GainMedkit();
		//This function is called so blueprints can handle animations and cutscenes after purchase.
		SuccessfulPurchase();
	}
}
