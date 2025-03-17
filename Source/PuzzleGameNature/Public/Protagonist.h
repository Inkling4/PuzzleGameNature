// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Protagonist.generated.h"

UCLASS()
class PUZZLEGAMENATURE_API AProtagonist : public ACharacter
{
	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* Camera;

public:
	// Sets default values for this character's properties
	AProtagonist();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputMappingContext* TheInputMappingContextFile;
	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* IA_Jump;

	void MoveInput(const FInputActionValue& InputValue);
	void JumpInput();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
