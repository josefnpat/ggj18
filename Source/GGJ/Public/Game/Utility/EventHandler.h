// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EventHandler.generated.h"


// Class for handling events. Based on this https://wiki.unrealengine.com/Simple_Global_Event_System
// However, instead of it being a component that is added to actors I am putting it in the game instance
// which can be accessed anywhere.

// Example delegate for when a "level" is complete (Might remove this) Check GGJCharacter.cpp for example use
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTelevision_AntennaRotated, bool, bReceptionAntenna, float, angularDistanceToCorrect);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTelevision_ChangeChannel, uint8, channelID);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FArm_GrabPressed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FArm_GrabReleased);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameWon);

UCLASS()
class GGJ_API UEventHandler : public UObject
{
	GENERATED_BODY()
	
public:
	UEventHandler();
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Television Events")
		FTelevision_AntennaRotated OnAntennaRotated;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Television Events")
		FTelevision_ChangeChannel OnChannelChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Arm Events")
		FArm_GrabPressed OnGrabPressed;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Arm Events")
		FArm_GrabReleased OnGrabReleased;

	UFUNCTION()
		void BindToOnAntennaRotated(UObject* obj, FName functionName);

	UFUNCTION()
		void BindToOnChannelChanged(UObject* obj, FName functionName);

	UFUNCTION()
		void BindToOnGrabPressed(UObject* obj, FName functionName);

	UFUNCTION()
		void BindToGrabReleased(UObject* obj, FName functionName);
	
};
