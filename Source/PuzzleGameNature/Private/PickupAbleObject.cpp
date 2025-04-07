// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupAbleObject.h"

// Sets default values
APickupAbleObject::APickupAbleObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the hitbox sphere
	PickupCollision = CreateDefaultSubobject<USphereComponent>("PickupCollision");
	PickupCollision->SetGenerateOverlapEvents(true);
	PickupCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APickupAbleObject::BeginPlay()
{
	Super::BeginPlay();
	//Points player actor ref to player actor
	PlayerActorRef = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());

	//Points Protagonist ref to player actor
	ProtagonistRef = Cast<AProtagonist>(PlayerActorRef);

	//Points player capsule ref to capsule component in the player
	PlayerCapsuleRef = Cast<UCapsuleComponent>(PlayerActorRef->GetComponentByClass(UCapsuleComponent::StaticClass()));

}

// Called every frame
void APickupAbleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerActorRef != nullptr && PickupCollision != nullptr)
	{
		if (PickupCollision->IsOverlappingComponent(PlayerCapsuleRef))
		{
			CollectItem();
		}

	}

}

//Function empty here, as it is intended to be overridden.
void APickupAbleObject::CollectItem()
{

}