// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "MedkitMerchant.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAMENATURE_API AMedkitMerchant : public AInteractableObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Shop")
	int32 MedkitPrice;
	virtual void BeginPlay() override;

public:
	AMedkitMerchant();
	virtual void Interact() override;
	//Called whenever you try to interact with the merchant with insufficient amounts of scrap.
	UFUNCTION(BlueprintImplementableEvent, category = "Shop")
	void InsufficientFunds();
	//Called whenever you do a successful purchase.
	//Note: Scrap and medkit math and purchase are already done by the time this function is called.
	UFUNCTION(BlueprintImplementableEvent, category = "Shop")
	void SuccessfulPurchase();
	//Called when you try to actually buy a medkit
	UFUNCTION(BlueprintCallable, category = "shop")
	void AttemptPurchase();
	//Blueprint function. Will make the shop widget show up on viewport.
	UFUNCTION(BlueprintImplementableEvent, category = "Shop")
	void OpenShop();
	//Blueprint function. Will make the shop widget disappear from the viewport.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, category = "Shop")
	void CloseShop();
};
