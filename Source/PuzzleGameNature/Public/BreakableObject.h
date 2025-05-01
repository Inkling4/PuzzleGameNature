// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableObject.generated.h"

UCLASS()
class PUZZLEGAMENATURE_API ABreakableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, category = "BreakableObjects")
	bool bIsOverlappingCrowbar;
	//Called right before the breakable object gets destroyed.
	UFUNCTION(BlueprintImplementableEvent, category = "BreakableObjects")
	void OnDestroy();
	UPROPERTY()
	TObjectPtr<AActor> PlayerActorRef;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
	void BreakObject();
	
};
