// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerEntity.h"
#include "Components/PlayerStatsComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

APlayerEntity::APlayerEntity() :ABaseEntity()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateOptionalDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SocketOffset = FVector(0, 20, 40);
	SpringArm->TargetArmLength = 125;
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	Camera->SetupAttachment(SpringArm);

	Pickaxe = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("Pickaxe")); 
	Pickaxe->SetupAttachment(GetMesh()); 

	PlayerStatsComponent = CreateOptionalDefaultSubobject<UPlayerStatsComponent>(TEXT("PlayerStatsComponent"));
}

void APlayerEntity::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
