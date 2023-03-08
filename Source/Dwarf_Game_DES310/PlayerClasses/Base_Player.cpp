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

	m_PlayerHeirloomPivot = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Player Heirloom Pivot")));
	m_PlayerHeirloomPivot->SetupAttachment(this->GetMesh());//Pivot point attaching to the mesh


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
	
	InputComponent->BindAction("StealHeirloom", IE_Pressed, this, &ABase_Player::StealHeirloom);

}

void ABase_Player::StealHeirloom()
{
	if (!mb_HasHeirloom) {
		if (mb_IsPlayerInRange) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("BUTTON PRESSED"));
			m_heirloom->SnapToPlayer(m_PlayerHeirloomPivot);
			mb_HasHeirloom = true;
		}
	}
}

