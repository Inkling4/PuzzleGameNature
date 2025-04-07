// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"


class AProtagonist;

UCLASS()
class PUZZLEGAMENATURE_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	TObjectPtr<AActor> PlayerActorRef;
	UPROPERTY()
	TObjectPtr<AProtagonist> ProtagonistRef;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Intended to be overridden
	virtual void Interact();

};
