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

	//Casts 
	PlayerActorRef = GetWorld()->GetFirstPlayerController()->GetPawn();

	
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

void ACameraRail::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (PlayerActorRef != nullptr)
	{
		float PlayerSpeedX = PlayerActorRef->GetVelocity().X;
		//Makes the speed framerate independent
		PlayerSpeedX = PlayerSpeedX * DeltaSeconds;
		//Moves camera every frame based on player velocity
		MoveCamera(true, PlayerSpeedX);
	}
	
}


/*
*Moves the camera one "step" along the rail.
*bForward decides if it will go forward or backward (negative or positive speed)
*Speed decides how far (in cm) it goes along the rail when called
*/
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


