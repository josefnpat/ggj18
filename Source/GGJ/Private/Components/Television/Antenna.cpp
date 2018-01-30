// Fill out your copyright notice in the Description page of Project Settings.

#include "Antenna.h"

#include "GGJ.h"

UAntenna::UAntenna()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAntenna::BeginPlay()
{
	Super::BeginPlay();
	Randomize();
}

void UAntenna::Randomize() {
	correctRotation.Yaw = FMath::FRandRange(0, 360);
	correctRotationVector = correctRotation.Vector();
	bCorrectPosition = false;
}

void UAntenna::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bGrabbed)
	{
		CheckAntennaRotation();
	}
}

void UAntenna::CheckAntennaRotation()
{
	float Angle = FMath::Abs(GetComponentRotation().Yaw + 180 - correctRotation.Yaw);

	if (Angle > 180)
	{
		Angle = FMath::Abs(Angle - 360);
		FMath::Abs(Angle);
	}

	if (Angle < rotationTolerance)
	{
		// Antenna is correct
		bCorrectPosition = true;
	}
	else
	{
		bCorrectPosition = false;
	}

	Cast<UGGJGameInstance>(GetWorld()->GetGameInstance())->GetEventHandler()->OnAntennaRotated.Broadcast(bReceptionAntenna, Angle);
}


