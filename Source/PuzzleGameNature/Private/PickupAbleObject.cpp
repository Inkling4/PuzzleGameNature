// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupAbleObject.h"
#include "Protagonist.h"

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
	PlayerActorRef = GetWorld()->GetFirstPlayerController()->GetPawn();
	PlayerActorRef->GetComponentByClass(UCapsuleComponent::StaticClass());

	//Points pointer to capsule component in the player
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
			APickupAbleObject::CollectItem();
		}

	}

}

void APickupAbleObject::CollectItem()
{
	
}