// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_PivotPoint = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Pivot point")));

	m_LodgePoint = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Lodge Point")));
	m_LodgePoint->SetRelativeLocation(FVector(12.93, 0, 18.87));
	m_LodgePoint->SetupAttachment(m_PivotPoint);


	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Pick")));
	m_Mesh->SetCollisionProfileName(TEXT("OverlapAll"));
	m_Mesh->SetRelativeLocation(FVector(-12.985,0, -18.4669));
	m_Mesh->SetupAttachment(m_LodgePoint);

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

