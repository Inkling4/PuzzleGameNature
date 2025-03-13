// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraRail.h"

#include "Components/SplineComponent.h"

//Activates when project/level starts
void ACameraRail::BeginPlay()
{
	CurrentPositionOnRail = 0.0;
}

//Moves the camera one "step" along the rail
void ACameraRail::MoveCamera()
{
	//Sets variable SplineLength to the length of the rail
	SplineLength = RailSplineComponent->GetSplineLength();

	//Displays debug message showing the function successfully called
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("Function \"Move Camera\" called!)"));
	

}

