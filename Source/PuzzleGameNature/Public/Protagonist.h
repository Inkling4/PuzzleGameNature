// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "BreakableObject.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Protagonist.generated.h"

UCLASS()
class PUZZLEGAMENATURE_API AProtagonist : public ACharacter
{
	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* Camera;

	//Declares the crowbar hitbox pointer
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CrowbarHitbox;
	class ABreakableObject* BreakableObjectptr1;
	UPROPERTY(meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> Actorptr;
	UPROPERTY(meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABreakableObject> BreakableObjectptr;
public:
	// Sets default values for this character's properties
	AProtagonist();
	void ChangeDirection();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputMappingContext* TheInputMappingContextFile;
	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* IA_Jump;
	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* IA_CrowbarAssault;
	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* IA_Interact;

	void MoveInput(const FInputActionValue& InputValue);
	void JumpInput();
	void CrowbarAssaultInput();
	void InteractInput();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
