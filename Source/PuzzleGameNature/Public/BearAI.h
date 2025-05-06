// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BearAI_PatrolPath.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CombatInterface.h"
#include "Animation/AnimMontage.h"
#include "BearAI.generated.h"

//Forward declaration
class USphereComponent;

UCLASS()

// Class also inherits from the combat interface
class PUZZLEGAMENATURE_API ABearAI : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABearAI();

	void MeleeAttack();
	
	
	//Returns the attack Hitbox of the Bear AI
	UFUNCTION(BlueprintCallable, category = "Bear")
	USphereComponent* GetBearAttackHitbox() const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Getter Functions
	UBehaviorTree* GetBehaviorTree() const;

	ABearAI_PatrolPath* GetBearAI_PatrolPath() const;

	UAnimMontage* GetMontage() const;


	// We implement the MeleeAttack here instead of in combat interface
	virtual int MeleeAttack_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Damage the bear deals to the player when it successfully hits
	UPROPERTY(EditAnywhere, category = "Bear")
	int32 AttackDamage;

private:

	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* BearAttackHitbox;
	

	//Sets these macros in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="true"))
	UBehaviorTree* Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="true"))
	ABearAI_PatrolPath* BearAI_PatrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage;

};
