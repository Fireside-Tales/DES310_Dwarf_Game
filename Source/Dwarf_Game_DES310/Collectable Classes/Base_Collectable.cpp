// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Collectable.h"

// Sets default values
ABase_Collectable::ABase_Collectable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->InitCapsuleSize(44.f, 60.f);
	Collider->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	Collider->SetRelativeLocation(FVector(0, 0, 60.f));
	Collider->SetSimulatePhysics(true);

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));;
	m_Mesh->SetupAttachment(Collider);

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

	mf_yawRotation += DeltaTime * rotationSpeed;

	if (mb_Bounce)
	{
		mf_yOffset += DeltaTime * bounceSpeed;
		if (mf_yOffset > 5)
		{
			mb_Bounce = false;
		}
	}
	else
	{
		mf_yOffset -= DeltaTime * bounceSpeed;
		if (mf_yOffset < 0)
		{
			mb_Bounce = true;
		}
	}

	m_Mesh->SetRelativeLocation(FVector(0,0, mf_yOffset));
	m_Mesh->SetRelativeRotation(FRotator(0, mf_yawRotation, 0));

}

