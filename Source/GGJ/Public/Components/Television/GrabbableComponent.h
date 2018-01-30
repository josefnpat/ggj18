// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GrabbableComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GGJ_API UGrabbableComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UGrabbableComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
		bool bGrabbed;

	UPROPERTY()
		bool bCorrectPosition;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
		float rotationSpeed = 2;

	UPROPERTY()
		FVector grabLocation;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
		FVector grabLocationOffset;

	UFUNCTION()
		virtual void RotateObject(float DeltaRotation);
};
