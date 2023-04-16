// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Actor.h"

// Sets default values
AAI_Actor::AAI_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mb_isAlive = true; 
}

// Called when the game starts or when spawned
void AAI_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mf_health < 0) 
	{
		mf_health = 0; 
		mb_isAlive = false;
	}


}

