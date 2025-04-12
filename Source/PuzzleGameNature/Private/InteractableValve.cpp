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
	
	if (ProtagonistRef->CheckIfEveryValveIsActive())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("All valves activated!"));
		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, TEXT("There are more valves remaining!"));
	}
	
}

bool AInteractableValve::GetValveActivationStatus() const
{
	return bIsValveActive;
}



void AInteractableValve::DisableValve()
{
	bIsValveActive = false;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Valve disabled!"));
}
