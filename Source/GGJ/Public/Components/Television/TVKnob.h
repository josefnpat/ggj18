// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrabbableComponent.h"
#include "TVKnob.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GGJ_API UTVKnob : public UGrabbableComponent
{
	GENERATED_BODY()
	
public:
	UTVKnob();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
		uint8 numOfChannels;

	UPROPERTY()
		float channelAngleHalfSize = -1;

	UPROPERTY()
		uint8 currentChannelID;

	UPROPERTY()
		uint8 correctChannel = 2;

	UPROPERTY()
		float currentChannelAngle;

	UFUNCTION()
		void ChangeChannel(uint8 channelID);

	UFUNCTION()
		void CheckKnobRotation();

	UFUNCTION()
		virtual void RotateObject(float DeltaRotation) override;
};
