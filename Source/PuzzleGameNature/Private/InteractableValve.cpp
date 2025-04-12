// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableValve.h"


//Defaults
AInteractableValve::AInteractableValve()
{
	ActiveValveTime = 3.0;
	bIsValveActive = false;
	
}

void AInteractableValve::Interact()
{
	Super::Interact();
	//Activates valve
	bIsValveActive = true;
	
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Valve activated!"));
	
	//Starts countdown for valve to turn off
	GetWorld()->GetTimerManager().SetTimer(ValveTimerHandle, this, &AInteractableValve::DisableValve, ActiveValveTime, false);
	
}

void AInteractableValve::DisableValve()
{
	bIsValveActive = false;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Valve disabled!"));
}
