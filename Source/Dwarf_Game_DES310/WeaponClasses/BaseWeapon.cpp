// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Pick")));
	m_Mesh->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = m_Mesh;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(FName(TEXT("Collider")));
	Collider->SetupAttachment(m_Mesh);

}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

