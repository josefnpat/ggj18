// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GGJGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_API AGGJGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGGJGameModeBase();

protected:
	virtual void StartPlay() override;
	
public:
	UPROPERTY(EditDefaultsOnly)
		class TSubclassOf<class AGGJPlayerController> controllerClass;

	UPROPERTY(EditDefaultsOnly)
		class TSubclassOf<class AArmPawn> playerOnePawnClass;

	UPROPERTY(EditDefaultsOnly)
		class TSubclassOf<class AArmPawn> playerTwoPawnClass;

	UPROPERTY()
		class AGGJPlayerController* player1;

	UPROPERTY()
		class AGGJPlayerController* player2;
};
