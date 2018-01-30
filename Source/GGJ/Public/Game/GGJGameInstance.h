// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GGJGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_API UGGJGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGGJGameInstance();
	
protected:
	virtual void Init() override;

public:
	UFUNCTION()
		class UEventHandler* GetEventHandler();

private:
	UPROPERTY()
		class UEventHandler* EventHandler;
	
};
