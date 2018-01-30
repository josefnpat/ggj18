// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ArmPawn.generated.h"

UCLASS()
class GGJ_API AArmPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AArmPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* root;

	UPROPERTY(EditDefaultsOnly)
		class UCapsuleComponent* armCollision;

	UPROPERTY(EditDefaultsOnly)
		class USkeletalMeshComponent* armMesh;

	UPROPERTY(EditDefaultsOnly)
		class USplineComponent* grabPathSpline;

	UPROPERTY(EditDefaultsOnly)
		float armSpeedMultiplier = 200.0f;

	UPROPERTY(EditDefaultsOnly)
		float SplineRotationSpeed = 45.0f;

	UPROPERTY(EditDefaultsOnly)
		float scalar = 100.0f;

	UPROPERTY(BlueprintReadOnly, Category="Gameplay")
		bool bGrabbing;

	UFUNCTION()
		class UGrabbableComponent* GetGrabbedObject();

	UFUNCTION()
		bool MoveTo(class UGrabbableComponent* obj);

	UFUNCTION()
		void GrabObject();

	UFUNCTION()
		void ReleaseObject();

	UFUNCTION()
		void MoveForward(bool engage);

	UFUNCTION()
		void Grab(bool engage);

	UFUNCTION()
		void RotateSpline();
	UFUNCTION()
		void TranslateAlong(float x, float y);
	UFUNCTION()
		void Rotate(float Val);
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void SetUserInput(bool state);

	UFUNCTION()
		void Reset();

private:

	UPROPERTY()
		class UGrabbableComponent* hoveredObject;

	UPROPERTY()
		class UGrabbableComponent* grabbedObject;

	UPROPERTY()
		bool bMoveForward = false;

	UPROPERTY()
		float distanceAlongSpline = 0;

	UPROPERTY()
		FVector CurrentLocation;

	UPROPERTY()
		FVector OriginalLocation;

	UPROPERTY()
		float target_x = 0.0f;

	UPROPERTY()
		float target_y = 0.0f;

	UPROPERTY()
		float current_x = 0.0f;

	UPROPERTY()
		float current_y = 0.0f;

	UPROPERTY()
		float vel_x = 0.0f;
	UPROPERTY()
		float vel_y = 0.0f;

	UPROPERTY(EditDefaultsOnly)
		float accel_scale = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float vel_scale = 2.25;

	UPROPERTY()
		bool isRight;

	UPROPERTY()
		bool userInput = true;

	UPROPERTY()
		FVector currentPosAuto;
	UPROPERTY()
		FVector targetPosAuto;
	UPROPERTY()
		FVector oldPosAuto;
};
