// Fill out your copyright notice in the Description page of Project Settings.


#include "BearAI_PatrolPath.h"

// Sets default values
ABearAI_PatrolPath::ABearAI_PatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PatrolPoints.Add(FVector(0, 0, 0));

}

FVector ABearAI_PatrolPath::GetPatrolPoint(int const index) const
{
	return PatrolPoints[index];
}

int ABearAI_PatrolPath::Num() const
{
	return PatrolPoints.Num();
}



