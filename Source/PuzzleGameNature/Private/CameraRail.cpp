// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraRail.h"

#include "Components/SplineComponent.h"

//Activates when project/level starts
void ACameraRail::BeginPlay()
{

	//Sets variable SplineLength to the length of the rail
	RailLength = RailSplineComponent->GetSplineLength();
}

//Moves the camera one "step" along the rail
void ACameraRail::MoveCamera(bool bForward)
{
	//Displays debug message showing the function successfully called
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Function \"Move Camera\" called!)"));

	//This variable is the size of the step the camera will move based off of the speed and length.
	float MovementFraction = RailSpeed / RailLength;
	//Moves the rail based on if it's forward or backward
	if (bForward)
	{
		CurrentPositionOnRail += MovementFraction;
	}
	else
	{
		CurrentPositionOnRail -= MovementFraction;
	}
	//Checks if it goes off the rail, and puts it back on
	if (CurrentPositionOnRail < 0.0)
	{
		CurrentPositionOnRail = 0.0;
	}
	if (CurrentPositionOnRail > 1.0)
	{
		CurrentPositionOnRail = 1.0;
	}
}

