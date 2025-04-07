// Fill out your copyright notice in the Description page of Project Settings.


#include "Deathbox.h"


void ADeathbox::CollectItem()
{
	Super::CollectItem();
	if (ProtagonistRef == nullptr) {return;}
	ProtagonistRef->GetHurt(100);
}
