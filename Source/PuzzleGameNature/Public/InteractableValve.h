// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "InteractableValve.generated.h"


/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API AInteractableValve : public AInteractableObject
{
	GENERATED_BODY()
	
protected:
	AInteractableValve();
	virtual void BeginPlay() override;
	FTimerHandle ValveTimerHandle;
	
	//Amount of seconds the valve is active once interacted with.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Valve")
	float ActiveValveTime;

	UPROPERTY(BlueprintReadOnly, category = "Valve")
	bool bIsValveActive;
	
	//Called whenever this valve is activated
	UFUNCTION(BlueprintImplementableEvent, category = "Valve")
	void ValveActivated();

	//Called whenever this valve is disabled
	UFUNCTION(BlueprintImplementableEvent, category = "Valve")
	void ValveDisabled();
	
	//Sets bIsValveActive to false
	UFUNCTION()
	void DisableValve();

	
public:
	
	
	
	virtual void Interact() override;

	//Returns bIsValveActive of this valve
	bool GetValveActivationStatus() const;
	


	
};
