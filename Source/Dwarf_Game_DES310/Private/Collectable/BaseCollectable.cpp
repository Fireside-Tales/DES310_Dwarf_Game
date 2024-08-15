// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable/BaseCollectable.h"
#include "Components/CapsuleComponent.h"
#include "Components/BounceRotationComponent.h"
// Sets default values
ABaseCollectable::ABaseCollectable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateOptionalDefaultSubobject<UCapsuleComponent>(FName("Collider"));
	RootComponent = Collider;

	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(Collider);

	Rotator = CreateOptionalDefaultSubobject<UBounceRotationComponent>(FName("Rotator"));
	
}

// Called when the game starts or when spawned
void ABaseCollectable::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseCollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

