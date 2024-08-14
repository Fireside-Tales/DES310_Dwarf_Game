// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerStatsComponent.h"

UPlayerStatsComponent::UPlayerStatsComponent() : Stamina(100.0f), MaxStamina(100.0f), DrainRate(10.0f), TargetTime(5.0f), Timer(0.0f), IsSprinting(false)
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPlayerStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	Stamina = MaxStamina;
}

void UPlayerStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsSprinting && GetOwner()->GetVelocity().Length() > 0 && Stamina > 0)
	{
		Timer = 0;

		Stamina -= DeltaTime * DrainRate;
		if (Stamina <= 0)
		{
			Stamina = 0;
			SetSprinting(false);
		}
	}
	else
	{
		Timer += DeltaTime;
		if (Timer > TargetTime)
		{
			Stamina += DeltaTime * DrainRate / 2;
			if (Stamina >= MaxStamina)
			{
				Stamina = MaxStamina;
			}
		}
	}
}

