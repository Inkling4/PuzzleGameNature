// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraRail.h"

#include <tiff.h> //idk why this include showed up, it just did

#include "Camera/CameraActor.h"
#include "Components/SplineComponent.h"

//Activates when project/level starts
void ACameraRail::BeginPlay()
{
	Super::BeginPlay();
	//Sets variable SplineLength to the length of the rail
	RailLength = RailSplineComponent->GetSplineLength();
}

//Constructor, sets default values and makes a camera
ACameraRail::ACameraRail(const FObjectInitializer& ObjectInitialier) : ACameraRig_Rail(ObjectInitialier)
{
	PrimaryActorTick.bCanEverTick = true;
	//Put in comment because We got issues making the camera a component rather than separate actor
	//Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	//Camera->SetupAttachment(RailCameraMount);
	RailSpeed = 500.0;
	RailLength = RailLength = RailSplineComponent->GetSplineLength();
}




//Moves the camera one "step" along the rail
void ACameraRail::MoveCamera(bool bForward, float Speed)
{
	//Displays debug message showing the function successfully called
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("Function \"Move Camera\" called!)"));

	//This variable is the size of the step the camera will move based off of the speed and length.
	float MovementFraction = Speed / RailLength;
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

