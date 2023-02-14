// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedural_Room.h"

// Sets default values
AProcedural_Room::AProcedural_Room()//You can't use overloaded constructors
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProcedural_Room::BeginPlay()
{
	Super::BeginPlay();//Don't delete this!! This is like Start() in Unity
	
}

void AProcedural_Room::KillPlayer()
{
}

void AProcedural_Room::KillPlayerWithTimer(float time)
{
}

// Called every frame
void AProcedural_Room::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);//Dont delete this!! This creates deltatime for the game loop

}

