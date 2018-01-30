// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AudioManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ_API UAudioManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAudioManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly)
		TArray<class USoundWave*> ChannelSounds;

	UPROPERTY(EditDefaultsOnly)
		TArray<USoundWave*> StaticSounds;

	UPROPERTY()
		class UAudioComponent* tvStaticAudioComponent;

	UPROPERTY()
		class UAudioComponent* tvChannelAudioComponent;

	UFUNCTION()
		void AntennaMoved(bool bReceptionAntenna, float antennaAngularDistanceToCorrect);

	UFUNCTION()
		void ChangeStaticAudio(uint8 channelID);

	UFUNCTION()
		void ChangeChannelAudio(uint8 channelID);
	
};
