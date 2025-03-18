// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraRig_Rail.h"
//#include "Camera/CameraComponent.h"
#include "CameraRail.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEGAMENATURE_API ACameraRail : public ACameraRig_Rail
{
	GENERATED_BODY()
	//UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* Camera;

public:
	ACameraRail(const FObjectInitializer& ObjectInitialier);
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, category = "Rail Controls")
	void MoveCamera(bool bForward, float Speed);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Rail Controls")
	float RailSpeed;
	UPROPERTY(VisibleAnywhere, category = "Rail Length")
	float RailLength;

};
