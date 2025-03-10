// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableGameMode.h"



void APlayableGameMode::StartPlay()
{
	Super::StartPlay();
	check(GEngine != nullptr);
}
