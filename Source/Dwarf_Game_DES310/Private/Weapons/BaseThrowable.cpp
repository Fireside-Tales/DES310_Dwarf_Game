// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseThrowable.h"

// Sets default values
ABaseThrowable::ABaseThrowable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseThrowable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseThrowable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseThrowable::OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

