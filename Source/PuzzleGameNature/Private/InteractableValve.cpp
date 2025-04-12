// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableValve.h"
#include "Protagonist.h"

//Defaults
AInteractableValve::AInteractableValve()
{
	ActiveValveTime = 3.0;
	bIsValveActive = false;
	
}

void AInteractableValve::BeginPlay()
{
	Super::BeginPlay();
	
}




void AInteractableValve::Interact()
{
	Super::Interact();
	//Activates valve
	bIsValveActive = true;
	
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Valve activated!"));
	
	//Starts countdown for valve to turn off
	GetWorld()->GetTimerManager().SetTimer(ValveTimerHandle, this, &AInteractableValve::DisableValve, ActiveValveTime, false);

	//Calls protagonist blueprint events
	if (ProtagonistRef->CheckIfEveryValveIsActive())
	{
		ProtagonistRef->EveryValveIsActive();
	}
	else
	{
		ProtagonistRef->ThereAreValvesRemaining();
	}
	
}

void AInteractableValve::DisableValve()
{
	bIsValveActive = false;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Valve disabled!"));
}

bool AInteractableValve::GetValveActivationStatus() const
{
	return bIsValveActive;
}


