// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Protagonist.h"
#include "PickupAbleObject.generated.h"

//Generic pickup class objects can derive from
UCLASS()
class PUZZLEGAMENATURE_API APickupAbleObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupAbleObject();

	UPROPERTY()
	TObjectPtr<AActor> PlayerActorRef;
	UPROPERTY()
	TObjectPtr<AProtagonist> ProtagonistRef;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* PickupCollision;

	UPROPERTY()
	TObjectPtr<UCapsuleComponent> PlayerCapsuleRef;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Runs when this actor touches the player. Can be overridden.
	virtual void CollectItem();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
