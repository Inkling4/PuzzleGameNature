// Fill out your copyright notice in the Description page of Project Settings.


#include "Protagonist.h"
#include "InputActionValue.h"

// Sets default values
AProtagonist::AProtagonist()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the hitbox for crowbar attacks
	CrowbarHitbox = CreateDefaultSubobject<USphereComponent>("CrowbarHitbox");
	CrowbarHitbox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProtagonist::BeginPlay()
{
	Super::BeginPlay();

	//Array of all actors in world with specified class (local variable)
	TArray<AActor*> OutputActors;

	//Gets all actors of class "ABreakableObject"
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABreakableObject::StaticClass(), OutputActors);
	//foreach loop that cycles through output array
	for (AActor* OutputActor : OutputActors)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("Found a breakable object in world!"));
	}
}

// Called every frame
void AProtagonist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AProtagonist::ChangeDirection();
	
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
/*
void AProtagonist::CrowbarAssaultInput()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Crowbar activated!"));
}

*/

void AProtagonist::InteractInput()
{
	
}

//Runs whenever you press the crowbar button
void AProtagonist::CrowbarAssaultInput()
{
	if (Actorptr == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Actor pointer is a null pointer :c"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Actor pointer is NOT a null pointer! :D"));
	}

	if (BreakableObjectptr == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Breakable Object is a null pointer :c"));
	}
	else
	{


		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Breakable Object is NOT a null pointer! :D"));
		if (CrowbarHitbox->IsOverlappingActor(Actorptr))
		{
		
		}

	}

}


//Function that sets rotation to velocity direction
void AProtagonist::ChangeDirection()
{
	bool bGreaterThanX = false;
	bool bLesserThanX = false;
	bool bGreaterThanY = false;
	bool bLesserThanY = false;
	FVector Velocity = GetVelocity();

	//TODO: Make diagonals have a speed threshold to make straight movement more often

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
