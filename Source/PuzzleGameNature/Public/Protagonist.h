// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Protagonist.generated.h"

//Forward declarations
class AInteractableObject;
class ABreakableObject;


UCLASS()
class PUZZLEGAMENATURE_API AProtagonist : public ACharacter
{
	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* Camera;

	//Declares the crowbar hitbox pointer
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CrowbarHitbox;

	

	

public:
	// Sets default values for this character's properties
	AProtagonist();
	void ChangeDirection();
	//Array of all actors in world with class "breakable object"
	UPROPERTY(VisibleAnywhere, category = "BreakableObjects")
	TArray<ABreakableObject*> BreakableObjectActors;
	//Array of all actors in the world with class "Interactable Object"
	UPROPERTY(VisibleAnywhere, category = "InteractableObjects")
	TArray<AInteractableObject*> InteractableObjectActors;
	



	
	//code below from: https://unrealcpp.com/on-overlap-begin/

	// declare overlap begin function
	UFUNCTION()
	void OnCrowbarOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnCrowbarOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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
	UPROPERTY(EditAnywhere, category = "EnhancedInput")
	class UInputAction* IA_Heal;

	void MoveInput(const FInputActionValue& InputValue);
	void JumpInput();
	void CrowbarAssaultInput();
	void InteractInput();
	void HealInput();

	//Stats

	UPROPERTY(VisibleAnywhere, category = "Stats")
	int32 Health;

	UPROPERTY(EditAnywhere, category = "Stats")
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, category = "Stats")
	int32 MedkitPower;

	//Inventory system!
	UPROPERTY(VisibleAnywhere, category = "Inventory")
	int32 MoneyScraps;
	UPROPERTY(VisibleAnywhere, category = "Inventory")
	bool bHasCrowbar;
	UPROPERTY(VisibleAnywhere, category = "Inventory")
	int32 Medkits;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Adds input parameter to total money count
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	void CollectMoneyScrap(int32 AmountOfScrap);
	//When called, sets bHasCrowbar to true
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	void CollectCrowbar();
	//Removes input parameter from money count
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	void LoseMoneyScrap(int32 MoneySpent);
	//Grants the player one medkit.
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	void GainMedkit();
	//Returns amount of scraps the player has.
	UFUNCTION (BlueprintCallable, category = "Inventory")
	int32 GetMoneyscraps() const;

	//Heals you MedkitPower health and spends a medkit if you have one. Returns true if healed successfully.
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	bool Heal();
	
	//Returns current health of player, as an integer
	UFUNCTION(BlueprintCallable, category = "Stats")
	int32 GetHealth() const;

	UFUNCTION(BlueprintCallable, category = "Stats")
	int32 GetMaxHealth() const;


	
	//Returns a reference to the crowbar hitbox
	USphereComponent* GetCrowbarHitbox() const;
	
};
