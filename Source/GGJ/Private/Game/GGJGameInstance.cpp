// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJGameInstance.h"

#include "EventHandler.h"


UGGJGameInstance::UGGJGameInstance()
{

}

void UGGJGameInstance::Init()
{
	Super::Init();

	EventHandler = NewObject<UEventHandler>(this, "EventHandler");
}

UEventHandler* UGGJGameInstance::GetEventHandler()
{
	return EventHandler;
}