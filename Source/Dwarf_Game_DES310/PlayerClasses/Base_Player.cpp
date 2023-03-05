// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Player.h"

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

	if (m_PlayerStates == PlayerStates::Dead) {
		mf_CurrentRespawnTimer -= DeltaTime;
	}
}

// Called to bind functionality to input
void ABase_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ReduceRespawnTimer", IE_Pressed, this, &ABase_Player::RespawnPlayer);
}

void ABase_Player::RespawnPlayer()
{
	if (InputComponent) {

		if (m_PlayerStates == PlayerStates::Dead) {
			if (mf_CurrentRespawnTimer == 0) {
				m_PlayerStates = PlayerStates::Respawning;
			}
			else {
				mf_CurrentRespawnTimer-=0.01;

			}
		}
	}
}

