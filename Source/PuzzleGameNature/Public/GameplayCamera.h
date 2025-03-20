// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CameraRail.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayCamera.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API AGameplayCamera : public ACameraActor
{
	GENERATED_BODY()
public:
	AGameplayCamera();
	//virtual void BeginPlay() override;
	TObjectPtr<AActor> RailActorPtr;
	TSharedPtr<ACameraRail> CameraRailPtr;
};
