// Fill out your copyright notice in the Description page of Project Settings.

#include "TVKnob.h"

#include "GGJ.h"

UTVKnob::UTVKnob()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTVKnob::BeginPlay()
{
	Super::BeginPlay();
}

void UTVKnob::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	cls();
	print(FString::Printf(TEXT("currentChannelID: %d"), currentChannelID));
	print(FString::Printf(TEXT("correctChannel: %d"), correctChannel));

	if (bGrabbed)
	{
		CheckKnobRotation();
	}
}

void UTVKnob::ChangeChannel(uint8 channelID)
{
	Cast<UGGJGameInstance>(GetWorld()->GetGameInstance())->GetEventHandler()->OnChannelChanged.Broadcast(channelID);
	currentChannelID = channelID;

	if (correctChannel == currentChannelID)
	{
		bCorrectPosition = true;
	}
	else
	{
		bCorrectPosition = false;
	}
}

void UTVKnob::CheckKnobRotation()
{
	// Init angle half size
	if (channelAngleHalfSize < 0)
	{
		channelAngleHalfSize = 360 / numOfChannels / 2;
	}

	// Distance to next channel for right and left
	float angleDifferenceLeft = GetComponentRotation().Pitch + 180 - (currentChannelAngle - channelAngleHalfSize);
	float angleDifferenceRight = GetComponentRotation().Pitch + 180 - (currentChannelAngle + channelAngleHalfSize);

	cls();
	print(FString::Printf(TEXT("ComponentRotation: %f"), GetComponentRotation().Pitch + 180));
	print(FString::Printf(TEXT("currentChannelAngle: %f"), currentChannelAngle));
	print(FString::Printf(TEXT("angleDifferenceLeft: %f"), angleDifferenceLeft));
	print(FString::Printf(TEXT("angleDifferenceRight: %f"), angleDifferenceRight));

	if (angleDifferenceLeft < 0)
	{
		currentChannelAngle -= channelAngleHalfSize * 2;
		--currentChannelID;

		if (currentChannelID < 0)
		{
			currentChannelID = numOfChannels - 1;
		}

		ChangeChannel(currentChannelID);
	}
	else if (angleDifferenceRight > 0)
	{
		currentChannelAngle += channelAngleHalfSize * 2;
		++currentChannelID;

		if (currentChannelID >= numOfChannels)
		{
			currentChannelID = 0;
		}

		ChangeChannel(currentChannelID);
	}

	currentChannelAngle = FMath::Abs(currentChannelAngle);
	if (currentChannelAngle > 360)
	{
		currentChannelAngle = currentChannelAngle - 360;
	}
}

void UTVKnob::RotateObject(float DeltaRotation)
{
	DeltaRotation *= rotationSpeed;

	FRotator rot = FRotator(0, 0, 0);
	rot.Pitch = DeltaRotation;

	grabLocationOffset = rot.RotateVector(grabLocationOffset);

	AddRelativeRotation(rot);

	grabLocation = GetComponentLocation() + grabLocationOffset;
}