// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableObject.h"
#include "Protagonist.h"

// Sets default values
ABreakableObject::ABreakableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsOverlappingCrowbar = false;

}

// Called when the game starts or when spawned
void ABreakableObject::BeginPlay()
{
	Super::BeginPlay();
	
	//Makes PlayerActorRef point to the player
	PlayerActorRef = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());

	
}

// Called every frame
void ABreakableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakableObject::BreakObject()
{
	if (PlayerActorRef == nullptr || GEngine == nullptr) {return;}
	if (IsOverlappingActor(PlayerActorRef))
	{
		//Calls blueprint function
		OnDestroy();
		//Actor disappears
		Destroy();
	}
}
