// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJPlayerController.h"
#include "GGJ.h"
#include "ArmPawn.h"
#include "GrabbableComponent.h"

// Sets default values
AGGJPlayerController::AGGJPlayerController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGGJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn())
	{
		// Find the other arm in the map so player 2 can possess it
		TArray<AActor*> foundArms;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArmPawn::StaticClass(), foundArms);

		for (int8 i = 0; i < foundArms.Num(); i++)
		{
			if (foundArms[i]->ActorHasTag("rightArm"))
			{
				// Possess the second arm
				Possess(Cast<APawn>(foundArms[i]));
				break;
			}
		}
	}

	armPawn = Cast<AArmPawn>(GetPawn());
}

void AGGJPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (armPawn) {
		armPawn->TranslateAlong(cache_left_x, cache_left_y);
	}
}

void AGGJPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("LeftAnalogX", this, &AGGJPlayerController::LeftAnalogX);
	InputComponent->BindAxis("LeftAnalogY", this, &AGGJPlayerController::LeftAnalogY);

	InputComponent->BindAxis("RightAnalogX", this, &AGGJPlayerController::RightAnalogX);
	InputComponent->BindAxis("RightAnalogY", this, &AGGJPlayerController::RightAnalogY);

	InputComponent->BindAction("Action", IE_Pressed, this, &AGGJPlayerController::ActionPressed);
	InputComponent->BindAction("Action", IE_Released, this, &AGGJPlayerController::ActionReleased);

	InputComponent->BindAction("Grab", IE_Pressed, this, &AGGJPlayerController::GrabPressed);
	InputComponent->BindAction("Grab", IE_Released, this, &AGGJPlayerController::GrabReleased);

	InputComponent->BindAction("Start", IE_Pressed, this, &AGGJPlayerController::StartPressed);
}

void AGGJPlayerController::LeftAnalogX(float Val)
{
	if (armPawn)
	{
		if (!armPawn->bGrabbing)
		{
			cache_left_x = Val;
		}
		else
		{
			if(armPawn->GetGrabbedObject())
				armPawn->GetGrabbedObject()->RotateObject(Val);
		}
	}
}

void AGGJPlayerController::LeftAnalogY(float Val)
{
	cache_left_y = Val;
	return;
}

void AGGJPlayerController::RightAnalogX(float Val)
{
	if (armPawn) {
		armPawn->Rotate(Val);
	}
	return;
}

void AGGJPlayerController::RightAnalogY(float Val)
{
	return;
}

void AGGJPlayerController::ActionPressed()
{
	if (armPawn) {
		armPawn->MoveForward(true);
	}
	return;
}

void AGGJPlayerController::ActionReleased()
{
	if (armPawn) {
		armPawn->MoveForward(false);
	}
	return;
}

void AGGJPlayerController::GrabPressed()
{
	if (armPawn) {
		armPawn->GrabObject();
	}
	return;
}

void AGGJPlayerController::GrabReleased()
{
	if (armPawn) {
		armPawn->ReleaseObject();
	}
	return;
}

void AGGJPlayerController::StartPressed()
{
	bStartPressed = true;
	return;
}

bool AGGJPlayerController::wasStartPressed()
{
	if (bStartPressed) {
		bStartPressed = false;
		return true;
	}
	return false;
}