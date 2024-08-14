// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageComponent.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

float UDamageComponent::CalculateDamage()
{
	float FinalDamage;

	return 0.0f;
}

float UDamageComponent::MeleeDamage()
{
	float MeleeDamage = 0;
	MeleeDamage = UKismetMathLibrary::RandomFloatInRange(MinDamageMult * 0.5f, MaxDamageMult * 1.5f);
	if (UKismetMathLibrary::RandomIntegerInRange(0, 100) < 10)
	{
		MeleeDamage *= 1.5;
	}
	return MeleeDamage;
}

float UDamageComponent::RangedDamage()
{
	// this need looked at

	return 0.0f;
}

float UDamageComponent::HazardDamage()
{
	// same as this
	return 0.0f;
}

