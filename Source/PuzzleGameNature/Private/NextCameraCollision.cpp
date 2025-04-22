// Fill out your copyright notice in the Description page of Project Settings.


#include "NextCameraCollision.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayCamera.h"
#include "Protagonist.h"

void ANextCameraCollision::CollectItem()
{
	Super::CollectItem();

	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameplayCamera::StaticClass(), CameraActors);
	for (auto CameraActor : CameraActors)
	{
		if (TObjectPtr<AGameplayCamera> CameraActorRef = Cast<AGameplayCamera>(CameraActor))
		{
			CameraActorRef->NextCamera();
			if (TObjectPtr<AProtagonist> PlayerRef = Cast<AProtagonist>(PlayerActorRef))
			{
				PlayerRef->SewerTeleport();
			}
		}
	}
}
