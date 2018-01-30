// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TVMaterialManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ_API UTVMaterialManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTVMaterialManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY()
		class UMaterialInstanceDynamic* staticMaterial;

	UPROPERTY()
		class UMaterialInstanceDynamic* channelImageMaterial;

	UPROPERTY(EditDefaultsOnly)
		TArray<class UTexture2D*> channelTextures;

	UFUNCTION()
		void ChangeScreenMaterialParameters(bool bReceptionAntenna, float antennaAngularDistanceToCorrect);
	
	UFUNCTION()
		void ChangeChannelImage(uint8 channelID);

	UFUNCTION()
		void ChangeStaticAmount(float staticAmount);

	UFUNCTION()
		void ChangeSaturationAmount(float saturationAmount);
};
