// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Player.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Dwarf_Game_DES310/WeaponClasses/PickaxeProjectile.h"

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

	InitialiseCamera(); // this sets up the camera for getting used for the aiming

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



	if (mb_Aiming)
	{
		FRotator AimRotation;
		FVector PlayerLoc = GetActorLocation();
		FVector forwardLocation = PlayerLoc + camera->GetForwardVector();

		FRotator newRot = UKismetMathLibrary::FindLookAtRotation(PlayerLoc, forwardLocation);

		AimRotation = FRotator(0, UKismetMathLibrary::RInterpTo(GetActorRotation(), newRot, DeltaTime, 15.f).Yaw, 0);

		GetCapsuleComponent()->SetWorldRotation(AimRotation);
	}

}

// Called to bind functionality to input
void ABase_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//InputComponent->BindAction("Aim", IE_Pressed, this, &ABase_Player::Aim);
	//InputComponent->BindAction("Aim", IE_Released, this, &ABase_Player::ReleaseAim);
	//InputComponent->BindAction("Throw", IE_Pressed, this, &ABase_Player::ThrowAxe); 

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

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Mouse Released")));
	m_PlayerStates = PlayerStates::Idle; 

	//if (m_AimHud)
	//{
	//	m_AimHud->RemoveFromViewport();
	//}
	mb_UseContRotation = false;
	mf_GamepadTurnRate = 1.5;
	mf_CameraTurnRate = 50.f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

}

void ABase_Player::ThrowAxe()
{

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Mouse Throw ")));

	//if (mb_axeThrown == false && mb_Aiming == true) 
	//{
	//	APickaxeProjectile* pickProjectile = Cast<APickaxeProjectile>(m_Pickaxe); 
	//	if (IsValid(pickProjectile)) 
	//	{
	//		const FDetachmentTransformRules* detachRules = new FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld,false);

	//		
	//		pickProjectile->ThrowAxe(); 
	//	}
	//	mb_axeThrown = true; 
	//}
}

void ABase_Player::SetSocketOffset(float input)
{
	input *= 0.5f; 
	FVector newOffset; 

	newOffset.X = mv_desiredSocketOffset.X - (input * 12.0f);
	newOffset.Y = mv_desiredSocketOffset.Y - (input * 4.0f);
	newOffset.Z = mv_desiredSocketOffset.Z + (input * 3.0f);

	SpringArmcomp->SocketOffset = newOffset; 

}

void ABase_Player::LerpCamera(float alpha)
{
	float armLength = UKismetMathLibrary::Lerp(mf_SpringIdleLength, mf_SpringAimLength, alpha);
	FVector cameraPos = FMath::Lerp(mv_CameraVec, mv_RangedCameraVec,alpha);

	SpringArmcomp->TargetArmLength = armLength; 
	mv_desiredSocketOffset = cameraPos; 
	SpringArmcomp->SocketOffset = cameraPos; 
}

void ABase_Player::HandlePlayerStates()
{
	if(mb_Aiming == false)
	{
		if (m_PlayerStates != PlayerStates::Throwing) 
		{
			if (GetCharacterMovement()->Velocity.Length() == 0)
			{
				m_PlayerStates = PlayerStates::Idle;
			}
			else
			{
				m_PlayerStates = PlayerStates::Moving;
			}			
		}
	}
	
}

void ABase_Player::InitialiseCamera()
{
	mv_CameraVec = FVector(0, 0, 0); // starting location for the camera
	mv_RangedCameraVec = FVector(0, 60, 65); // aimed location for the camera 

	mf_SpringIdleLength = 150.f; // starting length of the camera
	mf_SpringAimLength = 100.f;  // aim length for the camera

	SpringArmcomp->SocketOffset = mv_CameraVec; 
	SpringArmcomp->TargetArmLength = mf_SpringIdleLength; 

}

