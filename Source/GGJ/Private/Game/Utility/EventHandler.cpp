// Fill out your copyright notice in the Description page of Project Settings.

#include "EventHandler.h"

UEventHandler::UEventHandler()
{

}

void UEventHandler::BindToOnAntennaRotated(UObject* obj, FName functionName)
{
	TScriptDelegate<FWeakObjectPtr> delegate;
	delegate.BindUFunction(obj, functionName);
	OnAntennaRotated.Add(delegate);
}

void UEventHandler::BindToOnChannelChanged(UObject* obj, FName functionName)
{
	TScriptDelegate<FWeakObjectPtr> delegate;
	delegate.BindUFunction(obj, functionName);
	OnChannelChanged.Add(delegate);
}

void UEventHandler::BindToOnGrabPressed(UObject* obj, FName functionName)
{
	TScriptDelegate<FWeakObjectPtr> delegate;
	delegate.BindUFunction(obj, functionName);
	OnChannelChanged.Add(delegate);
}

void UEventHandler::BindToGrabReleased(UObject* obj, FName functionName)
{
	TScriptDelegate<FWeakObjectPtr> delegate;
	delegate.BindUFunction(obj, functionName);
	OnChannelChanged.Add(delegate);
}
