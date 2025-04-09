// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BearAI_PatrolPath.generated.h"

UCLASS()
class PUZZLEGAMENATURE_API ABearAI_PatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABearAI_PatrolPath();

	FVector GetPatrolPoint(int const index) const;
	int Num() const;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(MakeEditWidget="true", AllowPrivateAccess="true"))
	TArray<FVector> PatrolPoints;

};
