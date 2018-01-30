// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GGJPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_API AGGJPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGGJPlayerController();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	UPROPERTY()
		class AArmPawn* armPawn;

	UFUNCTION()
		void LeftAnalogX(float Val);

	UFUNCTION()
		void LeftAnalogY(float Val);

	UFUNCTION()
		void RightAnalogX(float Val);

	UFUNCTION()
		void RightAnalogY(float Val);

	UFUNCTION()
		void ActionPressed();

	UFUNCTION()
		void ActionReleased();

	UFUNCTION()
		void GrabPressed();

	UFUNCTION()
		void GrabReleased();

	UFUNCTION()
		void StartPressed();

	UFUNCTION()
		bool wasStartPressed();

private:
	UPROPERTY()
		float cache_left_x = 0.0f;
	UPROPERTY()
		float cache_left_y = 0.0f;
	UPROPERTY()
		bool bStartPressed = false;
	
};
