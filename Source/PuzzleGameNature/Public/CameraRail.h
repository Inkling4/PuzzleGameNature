// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraRig_Rail.h"
#include "CameraRail.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API ACameraRail : public ACameraRig_Rail
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, category = "Rail Controls")
	void MoveCamera();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Rail Controls")
	float RailSpeed = 0.0;
	UPROPERTY(VisibleAnywhere, category = "Rail Length")
	float SplineLength;
};
