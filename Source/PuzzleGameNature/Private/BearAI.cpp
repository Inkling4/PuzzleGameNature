// Fill out your copyright notice in the Description page of Project Settings.


#include "BearAI.h"

// Sets default values
ABearAI::ABearAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABearAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABearAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABearAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* ABearAI::GetBehaviorTree() const
{
	return Tree;
}

ABearAI_PatrolPath* ABearAI::GetBearAI_PatrolPath() const
{
	return BearAI_PatrolPath;
}


