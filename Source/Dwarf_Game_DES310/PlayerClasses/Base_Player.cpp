// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Player.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ABase_Player::ABase_Player()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmcomp = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("SpingArm")));
	SpringArmcomp->SocketOffset = FVector(0, 70, 65);
	SpringArmcomp->TargetArmLength = 150;
	SpringArmcomp->SetupAttachment(GetCapsuleComponent());

	m_PlayerStates = PlayerStates::Idle;

	camera = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Camera")));
	camera->SetupAttachment(SpringArmcomp);

	m_Pickaxe = CreateDefaultSubobject<UChildActorComponent>(FName(TEXT("Pickaxe")));
	m_Pickaxe->SetupAttachment(this->GetMesh());

}

// Called when the game starts or when spawned
void ABase_Player::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABase_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABase_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABase_Player::Aim()
{
	mb_Aiming = true;
	//if (IsValid(m_Widget))
	//{
	//	m_AimHud = CreateWidget(GetWorld(), m_Widget);
	//	m_AimHud->AddToViewport();
	//}
	mb_UseContRotation = true;

	mf_GamepadTurnRate = 0.75;
	mf_CameraTurnRate = 30.f;
	GetCharacterMovement()->MaxWalkSpeed = 250.0f;

}

void ABase_Player::ReleaseAim()
{
	mb_Aiming = false;

	//if (m_AimHud)
	//{
	//	m_AimHud->RemoveFromViewport();
	//}
	mb_UseContRotation = false;
	mf_GamepadTurnRate = 1.5;
	mf_CameraTurnRate = 50.f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

}

void ABase_Player::SetSocketOffset(float input)
{
}

void ABase_Player::LerpCamera(float alpha)
{
	//FVector camVec = 
}

