// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

#define print(text) if (GEngine){}// GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)
#define cls() if (GEngine) GEngine->ClearOnScreenDebugMessages();

#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "GGJStaticLibrary.h"
#include "GGJGameInstance.h"
#include "EventHandler.h"
