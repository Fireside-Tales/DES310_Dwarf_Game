// Fill out your copyright notice in the Description page of Project Settings.

//
#include "Components/BounceRotationComponent.h"

UBounceRotationComponent::UBounceRotationComponent() : BounceSpeed(100.0f)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBounceRotationComponent::BeginPlay()
{
	Super::BeginPlay();
	BounceTarget = GetOwner()->FindComponentByClass<UStaticMeshComponent>(); 
	if (BounceTarget)
	{
		StartLocation = BounceTarget->GetRelativeLocation();
	}
}

void UBounceRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (BounceTarget)
	{

		Time += BounceSpeed * DeltaTime;
		FVector NewLocation = StartLocation;
		NewLocation.Z += 10 * FMath::Sin(Time);

		BounceTarget->SetRelativeLocation(NewLocation);

	}
}
