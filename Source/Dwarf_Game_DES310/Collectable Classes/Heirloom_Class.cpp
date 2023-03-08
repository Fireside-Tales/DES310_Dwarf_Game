// Fill out your copyright notice in the Description page of Project Settings.


#include "Heirloom_Class.h"
#include "Components/CapsuleComponent.h"
#include "Dwarf_Game_DES310/PlayerClasses/Base_Player.h"

// Sets default values
AHeirloom_Class::AHeirloom_Class()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->InitCapsuleSize(44.f, 60.f);
	Collider->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	Collider->SetRelativeLocation(FVector(0, 0, 60.f));
	Collider->SetSimulatePhysics(true);

	m_HeirloomPivot = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Heirloom Pivot")));


	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	m_Mesh->SetupAttachment(Collider);//mesh attaching to the collider
	m_HeirloomPivot->SetupAttachment(m_Mesh);//Pivot point attaching to the mesh
	
}

// Called when the game starts or when spawned
void AHeirloom_Class::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHeirloom_Class::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeirloom_Class::SnapToPlayer(USceneComponent* dwarfHeirloomPivot)
{
	FAttachmentTransformRules heirloomAttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
	AttachToComponent(dwarfHeirloomPivot, heirloomAttachRules, "None");//Attaches the heirloom on the player
}

