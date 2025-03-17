// Fill out your copyright notice in the Description page of Project Settings.


#include "Protagonist.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AProtagonist::AProtagonist()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AProtagonist::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProtagonist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
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
