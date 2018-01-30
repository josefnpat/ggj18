// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Television.generated.h"

UCLASS()
class GGJ_API ATelevision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATelevision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly)
		class UAudioComponent* staticAudioComponent;

	UPROPERTY(EditDefaultsOnly)
		class UAudioComponent* channelAudioComponent;

	UPROPERTY(EditDefaultsOnly)
		class UAudioManager* audioManager;

	UPROPERTY(EditDefaultsOnly)
		class UTVMaterialManager* materialManager;

	UPROPERTY(EditDefaultsOnly)
		class UAntenna* antennaLeft;

	UPROPERTY(EditDefaultsOnly)
		class UAntenna* antennaRight;

	UPROPERTY(EditDefaultsOnly)
		class UTVKnob* knobLarge;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* knobSmall;
	
	UPROPERTY(EditAnywhere)
		class ACameraActor* camera;

	UPROPERTY()
		bool isAttractMode = true;

	UPROPERTY()
		FVector OriginalCameraLocation;

	UPROPERTY(EditAnywhere)
		class AActor* AttractCameraLocation;

	UPROPERTY()
		class AGGJPlayerController*  controller;

	UPROPERTY()
		class AArmPawn* leftArm;

	UPROPERTY()
		class AArmPawn* rightArm;

	UPROPERTY()
		bool gameOver = false;

};
