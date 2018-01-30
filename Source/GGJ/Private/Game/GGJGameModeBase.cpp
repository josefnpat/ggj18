// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJGameModeBase.h"

#include "GGJ.h"
#include "GGJPlayerController.h"
#include "ArmPawn.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AGGJGameModeBase::AGGJGameModeBase()
{

}

void AGGJGameModeBase::StartPlay()
{
	Super::StartPlay();

	UWorld* world = GetWorld();

	// Store player controllers
	player1 = Cast<AGGJPlayerController>(UGameplayStatics::GetPlayerController(world, 0));
	player2 = Cast<AGGJPlayerController>(UGameplayStatics::GetPlayerController(world, 1));

	if (GetGameInstance()->GetNumLocalPlayers() < 2)
	{
		UGameplayStatics::CreatePlayer(world, -1, false);
	}

	if (!player2)
	{
		player2 = world->SpawnActor<AGGJPlayerController>(controllerClass);
	}

	GetGameInstance()->GetLocalPlayerByIndex(1)->SwitchController(player2);
}
