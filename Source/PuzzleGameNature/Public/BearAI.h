// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BearAI_PatrolPath.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "BearAI.generated.h"

UCLASS()
class PUZZLEGAMENATURE_API ABearAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABearAI();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTree() const;

	ABearAI_PatrolPath* GetBearAI_PatrolPath() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="true"))
	UBehaviorTree* Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="true"))
	ABearAI_PatrolPath* BearAI_PatrolPath;

};
