// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIEntity.h"
#include "Components/StatsComponent.h"
AAIEntity::AAIEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	StatsComponent = CreateOptionalDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));

}

void AAIEntity::BeginPlay()
{
	Super::BeginPlay();
}

void AAIEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
