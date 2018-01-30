// Fill out your copyright notice in the Description page of Project Settings.

#include "GrabbableComponent.h"

#include "GGJ.h"

UGrabbableComponent::UGrabbableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabbableComponent::BeginPlay()
{
	Super::BeginPlay();

	grabLocation = GetComponentLocation() + grabLocationOffset;
}

void UGrabbableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabbableComponent::RotateObject(float DeltaRotation)
{
	DeltaRotation *= rotationSpeed;

	FRotator rot = FRotator(0,0,0);
	rot.Yaw = DeltaRotation;

	grabLocationOffset = rot.RotateVector(grabLocationOffset);

	AddRelativeRotation(rot);

	grabLocation = GetComponentLocation() + grabLocationOffset;
}