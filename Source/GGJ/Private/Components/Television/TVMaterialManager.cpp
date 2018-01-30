// Fill out your copyright notice in the Description page of Project Settings.

#include "TVMaterialManager.h"

#include "GGJ.h"

// Sets default values for this component's properties
UTVMaterialManager::UTVMaterialManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTVMaterialManager::BeginPlay()
{
	Super::BeginPlay();
	
	Cast<UGGJGameInstance>(GetWorld()->GetGameInstance())->GetEventHandler()->BindToOnAntennaRotated(this, "ChangeScreenMaterialParameters");
	Cast<UGGJGameInstance>(GetWorld()->GetGameInstance())->GetEventHandler()->BindToOnChannelChanged(this, "ChangeChannelImage");
}

void UTVMaterialManager::ChangeScreenMaterialParameters(bool bReceptionAntenna, float antennaAngularDistanceToCorrect)
{
	float normalizedAntenna = FMath::Clamp(antennaAngularDistanceToCorrect / 90, 0.0f, 1.0f);

	if (bReceptionAntenna)
	{
		// Modify static parameter
		staticMaterial->SetScalarParameterValue("StaticAmount", normalizedAntenna);
		print(FString::Printf(TEXT("bReceptionAntenna: %f"), normalizedAntenna));
	}
	else
	{
		// Modify saturation parameter
		channelImageMaterial->SetScalarParameterValue("TVImageSaturation", normalizedAntenna);
		print(FString::Printf(TEXT("bSaturationAntenna: %f"), normalizedAntenna));
	}
}

void UTVMaterialManager::ChangeChannelImage(uint8 channelID)
{
	if (channelID < channelTextures.Num())
	{
		channelImageMaterial->SetTextureParameterValue("TVImage", channelTextures[channelID]);
	}
}

void UTVMaterialManager::ChangeStaticAmount(float staticAmount)
{
	FMath::Clamp(staticAmount, 0.0f, 1.0f);
	staticMaterial->SetScalarParameterValue("StaticAmount", staticAmount);
}

void UTVMaterialManager::ChangeSaturationAmount(float saturationAmount)
{
	FMath::Clamp(saturationAmount, 0.0f, 1.0f);
	channelImageMaterial->SetScalarParameterValue("TVImageSaturation", saturationAmount);
}
