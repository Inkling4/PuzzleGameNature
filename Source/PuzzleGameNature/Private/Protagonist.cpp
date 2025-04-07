// Fill out your copyright notice in the Description page of Project Settings.


#include "Protagonist.h"
#include "InputActionValue.h"
#include "BreakableObject.h"
#include "InteractableObject.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

// Sets default values
AProtagonist::AProtagonist()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Just defaults, edit in editor if needed.
	MaxHealth = 5;
	MedkitPower = 3;
	Medkits = 0;
	

	//Creates the hitbox for crowbar attacks
	CrowbarHitbox = CreateDefaultSubobject<USphereComponent>("CrowbarHitbox");
	CrowbarHitbox->SetGenerateOverlapEvents(true);
	CrowbarHitbox->SetupAttachment(RootComponent);
	//Code from https://unrealcpp.com/on-overlap-begin/
	CrowbarHitbox->OnComponentBeginOverlap.AddDynamic(this, &AProtagonist::OnCrowbarOverlapBegin);
	CrowbarHitbox->OnComponentEndOverlap.AddDynamic(this, &AProtagonist::OnCrowbarOverlapEnd);
	



	//Stimulus Source
	SetupStimulusSource();

}

// Called when the game starts or when spawned
void AProtagonist::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	bHasCrowbar = false;

	// Not currently in use for anything, which is why it's in comments.
	
	//temp array
	TArray<AActor*> TempBreakActors;

	//Gets all actors of class "ABreakableObject".
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABreakableObject::StaticClass(), TempBreakActors);
	//foreach loop that cycles through output array
	for (auto Actor : TempBreakActors)
	{
		ABreakableObject* BreakableActor = Cast<ABreakableObject>(Actor);
		BreakableObjectActors.Add(BreakableActor);
	}

	//Gets all child actors of "InteractableObject"
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInteractableObject::StaticClass(), TempBreakActors);
	for (auto TempBreakActor : TempBreakActors)
	{
		AInteractableObject* InteractableActor = Cast<AInteractableObject>(TempBreakActor);
		InteractableObjectActors.Add(InteractableActor);
	}

}

// Called every frame
void AProtagonist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AProtagonist::ChangeDirection();
	
}

// Called to bind functionality to input
void AProtagonist::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(TheInputMappingContextFile, 0);
		}
	}
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AProtagonist::MoveInput);
		Input->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AProtagonist::JumpInput);
		Input->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &AProtagonist::InteractInput);
		Input->BindAction(IA_CrowbarAssault, ETriggerEvent::Triggered, this, &AProtagonist::CrowbarAssaultInput);
		Input->BindAction(IA_Heal, ETriggerEvent::Triggered, this, &AProtagonist::HealInput);
	}


}

void AProtagonist::MoveInput(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddMovementInput(FVector{ 1,0,0, }, InputVector.X);
		AddMovementInput(FVector{ 0,1,0 }, InputVector.Y);

	}
}

void AProtagonist::JumpInput()
{
	AProtagonist::Jump(); //Jumps. Thanks UE for making a jump button for us!
}


void AProtagonist::InteractInput()
{
	for (auto InteractableActor : InteractableObjectActors)
	{
		if (CrowbarHitbox == nullptr) {return;}
		if (CrowbarHitbox->IsOverlappingActor(InteractableActor))
		{
			TObjectPtr<AInteractableObject> InteractableActorRef = Cast<AInteractableObject>(InteractableActor);
			InteractableActorRef->Interact();
		}

	}
}

//Runs whenever you press the crowbar button
//Destroys any breakable object in front of the player if the player has a crowbar
void AProtagonist::CrowbarAssaultInput()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Crowbar input called!"));
	if (bHasCrowbar)
	{
		for (auto BreakableActor : BreakableObjectActors)
		{
			if (CrowbarHitbox->IsOverlappingActor(BreakableActor))
			{
				TObjectPtr<ABreakableObject> BreakableActorRef = Cast<ABreakableObject>(BreakableActor);
				BreakableActorRef->BreakObject();
			}

		}
	}
}



void AProtagonist::HealInput()
{
	Heal();
}




/*
*Function that sets rotation to velocity direction.
*No longer in use, as I just toggled a setting instead in BP.
*/
void AProtagonist::ChangeDirection()
{
	bool bGreaterThanX = false;
	bool bLesserThanX = false;
	bool bGreaterThanY = false;
	bool bLesserThanY = false;
	FVector Velocity = GetVelocity();


	//Sets booleans for if the speed is higher or lower than 0
	if (Velocity.X > 0) { bGreaterThanX = true; }
	if (Velocity.X < 0) { bLesserThanX = true; }
	if (Velocity.Y > 0) { bGreaterThanY = true; }
	if (Velocity.Y < 0) { bLesserThanY = true; }

	//8 if statements for different rotations

	if (bGreaterThanX)
	{
		if (bGreaterThanY)
		{
			SetActorRotation({ 0,45,0 });
		}
		else if (bLesserThanY)
		{
			SetActorRotation({ 0,-45,0 });
		}
		else
		{
			SetActorRotation({ 0,0,0, });
		}
	}

	if (bGreaterThanY and !bGreaterThanX)
	{
		if (bLesserThanX)
		{
			SetActorRotation({ 0, 135, 0 });
		}
		else
		{
			SetActorRotation({ 0, 90, 0 });
		}
	}

	if (bLesserThanX and !bGreaterThanY)
	{
		if (bLesserThanY)
		{
			SetActorRotation({ 0,-135,0 });
		}
		else
		{
			SetActorRotation({ 0, 180, 0 });
		}
	}
	if (bLesserThanY and !bGreaterThanX and !bLesserThanX)
	{
		SetActorRotation({ 0,-90,0 });
	}
}


void AProtagonist::OnCrowbarOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//null pointer check, for safety
	if (GEngine == nullptr || OtherActor == nullptr) { return; }

	//Test to see if function is called
	//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, TEXT("Crowbar overlap called!"));


	/*
	//Checks if other actor is a child of breakable object
	if (OtherActor->GetClass()->IsChildOf(ABreakableObject::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Blue, TEXT("Crowbar on Breakable object overlap called!"));

		TObjectPtr<ABreakableObject> BreakableObjectRef = Cast<ABreakableObject>(OtherActor);
		if (BreakableObjectRef != nullptr)
		{
			BreakableObjectRef->BreakObject();
		}
	}
	*/
}


void AProtagonist::OnCrowbarOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//null pointer check, for safety
	if (GEngine == nullptr || OtherActor == nullptr) { return; }

	//Checks if other actor is a child of breakable object
	if (OtherActor->GetClass()->IsChildOf(ABreakableObject::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Magenta, TEXT("Crowbar on Breakable object overlap end called!"));
	}

}

//Inventory!

void AProtagonist::CollectMoneyScrap(int32 AmountOfScrap)
{
	MoneyScraps += AmountOfScrap;
}

void AProtagonist::LoseMoneyScrap(int32 MoneySpent)
{
	MoneyScraps -= MoneySpent;
}
int32 AProtagonist::GetMoneyscraps() const
{
	return MoneyScraps;
}



void AProtagonist::CollectCrowbar()
{
	bHasCrowbar = true;
}

int32 AProtagonist::GetHealth() const
{
	return Health;
}

bool AProtagonist::Heal()
{
	//Checks if you even have a medkit to use
	if (Medkits > 0)
	{
		Health += MedkitPower;
		Medkits--;
		//Makes sure health doesn't go above max
		if (Health > MaxHealth)
		{
			Health = MaxHealth;
		}
		return true;
	}
	return false;
}

void AProtagonist::GainMedkit()
{
	Medkits++;
}

USphereComponent* AProtagonist::GetCrowbarHitbox() const
{
	return CrowbarHitbox;
}


//Stimulus Source for bear AI to react to
void AProtagonist::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}