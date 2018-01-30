// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioManager.h"

#include "GGJ.h"

// Sets default values for this component's properties
UAudioManager::UAudioManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAudioManager::BeginPlay()
{
	Super::BeginPlay();

	Cast<UGGJGameInstance>(GetWorld()->GetGameInstance())->GetEventHandler()->BindToOnAntennaRotated(this, "AntennaMoved");

	Cast<UGGJGameInstance>(GetWorld()->GetGameInstance())->GetEventHandler()->BindToOnChannelChanged(this, "ChangeStaticAudio");
	Cast<UGGJGameInstance>(GetWorld()->GetGameInstance())->GetEventHandler()->BindToOnChannelChanged(this, "ChangeChannelAudio");

	int8 soundIndex = FMath::RandRange(0, StaticSounds.Num() - 1);
}


// Called every frame
void UAudioManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAudioManager::AntennaMoved(bool bReceptionAntenna, float antennaAngularDistanceToCorrect)
{
	float normalizedAntenna = antennaAngularDistanceToCorrect / 90;

	if (bReceptionAntenna)
	{
		tvStaticAudioComponent->AdjustVolume(0.1f, normalizedAntenna);
		tvChannelAudioComponent->AdjustVolume(0.1f, FMath::Abs(normalizedAntenna-1));

		print(FString::Printf(TEXT("Channel volume: %f"), FMath::Abs(normalizedAntenna - 1)));
	}
}

void UAudioManager::ChangeStaticAudio(uint8 channelID)
{
	int8 soundIndex = FMath::RandRange(0, StaticSounds.Num() - 1);

	tvStaticAudioComponent->AdjustVolume(0.5f, 1.0f);
	tvStaticAudioComponent->SetSound(StaticSounds[soundIndex]);
}

void UAudioManager::ChangeChannelAudio(uint8 channelID)
{
	tvChannelAudioComponent->SetSound(ChannelSounds[channelID]);
}
