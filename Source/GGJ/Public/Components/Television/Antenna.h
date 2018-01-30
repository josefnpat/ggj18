// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrabbableComponent.h"
#include "Antenna.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GGJ_API UAntenna : public UGrabbableComponent
{
	GENERATED_BODY()
	
public:
	UAntenna();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
		FRotator correctRotation;

	UPROPERTY()
		FVector correctRotationVector;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		float rotationTolerance = 5.0;

	UPROPERTY(EditDefaultsOnly)
		bool bReceptionAntenna;
	
	UFUNCTION()
		void CheckAntennaRotation();

	UFUNCTION()
		void Randomize();
};
