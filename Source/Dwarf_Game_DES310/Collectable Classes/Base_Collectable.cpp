// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Collectable.h"

// Sets default values
ABase_Collectable::ABase_Collectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase_Collectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_Collectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

