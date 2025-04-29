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
class AInteractableValve;

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
	
	
	//Returns whether every InteractableValve in the current level is active or not.
	//Returns false if even a single valve is not active.
	UFUNCTION(BlueprintCallable, category = "Valve")
	bool CheckIfEveryValveIsActive();

	//Called when you activate the last valve and every valve is active.
	UFUNCTION(BlueprintImplementableEvent, category = "Valve")
	void EveryValveIsActive();

	//Called when you activate a valve, but not every valve is active.
	UFUNCTION(BlueprintImplementableEvent, category = "Valve")
	void ThereAreValvesRemaining();
	
protected:
	//Amount of instances of InteractableValve there is in the current level.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Valve")
	int32 AmountOfValvesInLevel;

	//List of all Interactable Valves in level
	UPROPERTY(VisibleAnywhere, category = "Valve")
	TArray<AInteractableValve*> ValveActors;

	
public:

	
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
	
	FTimerHandle CrowbarTimerHandle;
	//Destroys overlapping crowbarhitbox breakable actors	
	void SmashCrowbar();

	//Amount of time (in seconds) it takes from when you input crowbar to when it actually destroys things.
	//For animation syncing purposes.
	UPROPERTY(EditAnywhere, category = "Animation")
	float TimeToSwingCrowbar;

	
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

	//Animation things

	//Runs whenever crowbar action succeeds
	UFUNCTION(BlueprintImplementableEvent, category = "Animation")
	void CrowbarAnimation();

	UPROPERTY(EditDefaultsOnly, category = "Sewer")
	FVector SewerCoordinates {0,0,0};
	
public:	
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
	//Teleports player to sewer goal coordinates.
	UFUNCTION(BlueprintCallable, category = "Sewer")
	void SewerTeleport();
	
	//Adds input parameter to total money count
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	void CollectMoneyScrap(int32 AmountOfScrap);
	//Sets MoneyScrap to new value
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	void SetMoneyScraps(int32 inScrap);
	//Sets bHasCrowbar to true
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	void CollectCrowbar();
	//Sets bHasCrowbar to false
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	void LoseCrowbar();
	//Removes input parameter from money count
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	void LoseMoneyScrap(int32 MoneySpent);
	//Grants the player one medkit.
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")
	void GainMedkit();
	//Returns amount of medkits in player inventory
	UFUNCTION(BlueprintCallable, category = "Inventory")
	int32 GetMedkits() const;
	//Sets new value for amount of medkits.
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Inventory")	
	void SetMedkits(int32 InMedkits);
	//Returns amount of scraps the player has.
	UFUNCTION (BlueprintCallable, category = "Inventory")
	int32 GetMoneyscraps() const;

	//Heals you MedkitPower health and spends a medkit if it succeeded.
	//Returns 0 on success, 1 if you don't have any medkits, and 2 if you have medkits, but are at full health.
	UFUNCTION(BlueprintCallable, category = "Inventory")
	int32 Heal();

	UFUNCTION(BlueprintImplementableEvent, category = "Inventory")
	void SuccessfulHeal();

	//Called whenever you try to heal, but have no medkits.
	UFUNCTION(BlueprintImplementableEvent, category = "Inventory")
	void NoMedkits();

	//Called whenever you try to heal and you do have medkits, but you are at full health.
	UFUNCTION(BlueprintImplementableEvent, category = "Inventory")
	void HealFailureFullHealth();
	
	//Returns current health of player, as an integer
	UFUNCTION(BlueprintCallable, category = "Stats")
	int32 GetHealth() const;

	UFUNCTION(BlueprintCallable, category = "Stats")
	int32 GetMaxHealth() const;

	//Loses health.
	//Damage: amount of health subtracted.
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Stats")
	void GetHurt(int32 Damage);
	
	//Sets health to new value. Cannot go above Maximum health, or below 0.
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Stats")
	void SetHealth(int32 InHealth);

	
	
	//Returns a reference to the crowbar hitbox
	USphereComponent* GetCrowbarHitbox() const;
	

	private:
		// Stimulus Source for the bear AI to react to
		class UAIPerceptionStimuliSourceComponent* StimulusSource;

		void SetupStimulusSource();
};
