// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Player.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Dwarf_Game_DES310/WeaponClasses/PickaxeProjectile.h"
#include "Containers/Queue.h"

// Sets default values
ABase_Player::ABase_Player()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmcomp = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("SpingArm")));
	SpringArmcomp->SocketOffset = FVector(0, 20, 40);
	SpringArmcomp->TargetArmLength = 125;
	SpringArmcomp->SetupAttachment(GetCapsuleComponent());

	m_PlayerStates = PlayerStates::Idle;

	camera = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Camera")));
	camera->SetupAttachment(SpringArmcomp);

	m_Pickaxe = CreateDefaultSubobject<UChildActorComponent>(FName(TEXT("Pickaxe")));
	m_Pickaxe->SetupAttachment(this->GetMesh());

	m_PlayerHeirloomPivot = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Player Heirloom Pivot")));
	m_PlayerHeirloomPivot->SetupAttachment(this->GetMesh());//Pivot point attaching to the mesh

	InitialiseCamera(); // this sets up the camera for getting used for the aiming
	mb_AttackFinished = true;
}

// Called when the game starts or when spawned
void ABase_Player::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerStats.mf_Health = m_PlayerStats.mf_MaxHealth;
	m_PlayerStats.mf_Strength = m_PlayerStats.mf_BaseStrength;
	m_PlayerStats.mf_Movespeed = m_PlayerStats.mf_BaseMovespeed;
	m_PlayerStats.mf_SwingSpeed = m_PlayerStats.mf_SwingSpeed;
	m_PlayerStats.mf_Stamina = m_PlayerStats.mf_MaxStamina;
}

// Called every frame
void ABase_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandlePlayerStats(); // handles the clamping of the players stats
	HandleAttacks(); // Handles the queue for the players attacks
	HandlePlayerStates(); // handles all the players states

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

	InputComponent->BindAction("StealHeirloom", IE_Pressed, this, &ABase_Player::StealHeirloom);
	InputComponent->BindAction("Throw", IE_Pressed, this, &ABase_Player::ThrowInput);
	InputComponent->BindAction("Light Attack", IE_Pressed, this, &ABase_Player::LightAttackInput);
	InputComponent->BindAction("Heavy Attack", IE_Pressed, this, &ABase_Player::HeavyAttackInput);


	InputComponent->BindAction("PlayerDash", IE_Pressed, this, &ABase_Player::ToggleDash);
	InputComponent->BindAction("PlayerDash", IE_Released, this, &ABase_Player::ToggleDash);
}

void ABase_Player::ThrowInput()
{
	if (mb_Aiming)  // checks that the player is aiming
	{
		if (IsValid(m_AxeRef)) // checks if the axe is set
		{
			if (m_AxeRef->mb_Thrown == false)  // checks if it has been thrown yet
			{
				m_PlayerStates = PlayerStates::Throwing; // sets the player state to throwing
			}
		}
	}
}

void ABase_Player::LightAttackInput()
{
	if (m_AxeRef->mb_Thrown == false && mb_Aiming == false) // checks if the axe has not been thrown and the player isn't aiming
	{
		if (m_PlayerStates != PlayerStates::Attacking)
		{
			if (m_PlayerStates != PlayerStates::Throwing)
			{
				m_PlayerStates = PlayerStates::Attacking;
				m_NextAttack.Enqueue(PlayerAttacks::Light1);
				mb_AttackFinished = true;
			}
		}
		else
		{
			if (m_NextAttack.IsEmpty())
			{
				switch (m_CurrentAttack)
				{
				case PlayerAttacks::Light1:
					m_NextAttack.Enqueue(PlayerAttacks::Light2);
					break;
				case PlayerAttacks::Light2:
					m_NextAttack.Enqueue(PlayerAttacks::Light3);
					break;
				case PlayerAttacks::Light3:
					m_NextAttack.Enqueue(PlayerAttacks::Light1);
					break;
				}
			}
		}
	}
}
void ABase_Player::HeavyAttackInput()
{
	if (m_AxeRef->mb_Thrown == false && mb_Aiming == false)
	{
		if (m_PlayerStates != PlayerStates::Attacking)
		{
			if (m_PlayerStates != PlayerStates::Throwing)
			{
				m_PlayerStates = PlayerStates::Attacking;
				m_NextAttack.Enqueue(PlayerAttacks::Heavy1);
				mb_AttackFinished = true;
			}
		}
		else
		{
			if (m_NextAttack.IsEmpty())
			{
				switch (m_CurrentAttack)
				{
				case PlayerAttacks::Heavy1:
					m_NextAttack.Enqueue(PlayerAttacks::Heavy2);
					break;
				case PlayerAttacks::Heavy2:
					m_NextAttack.Enqueue(PlayerAttacks::Heavy3);
					break;
				case PlayerAttacks::Heavy3:
					m_NextAttack.Enqueue(PlayerAttacks::Heavy1);
					break;
				}
			}
		}
	}
}
void ABase_Player::HandleAttacks()
{
	if (mb_AttackFinished)
	{
		if (m_NextAttack.IsEmpty() == false)
		{
			m_NextAttack.Dequeue(m_CurrentAttack);
			mb_AttackFinished = false;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("DEqueued")));


		}
		else
		{
			m_CurrentAttack = PlayerAttacks::None;
			m_PlayerStates = PlayerStates::Idle;
			mb_AttackFinished = false;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("FINISHED ATTACK")));

		}
	}
}


void ABase_Player::Aim()
{
	mb_Aiming = true;
	m_PlayerStates = PlayerStates::Aiming;
	mb_UseContRotation = true;
	mf_GamepadTurnRate = 0.75;
	mf_CameraTurnRate = 30.f;
	GetCharacterMovement()->MaxWalkSpeed = 250.0f;

}

void ABase_Player::ReleaseAim()
{
	mb_Aiming = false;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Mouse Released")));
	if (m_PlayerStates != PlayerStates::Throwing)
	{
		m_PlayerStates = PlayerStates::Idle;
	}


	mb_UseContRotation = false;
	mf_GamepadTurnRate = 1.5;
	mf_CameraTurnRate = 50.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

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
	FVector cameraPos = FMath::Lerp(mv_CameraVec, mv_RangedCameraVec, alpha);

	SpringArmcomp->TargetArmLength = armLength;
	mv_desiredSocketOffset = cameraPos;
	SpringArmcomp->SocketOffset = cameraPos;
}

void ABase_Player::HandlePlayerStates()
{
	if (m_PlayerStats.isAlive)
	{
		if (mb_Aiming == false)
		{
			switch (m_PlayerStates)
			{
			case PlayerStates::Throwing:
				break;
			case PlayerStates::Attacking:

				break;
			default:
				if (GetCharacterMovement()->Velocity.Length() == 0)
				{
					m_PlayerStates = PlayerStates::Idle;
				}
				else
				{
					m_PlayerStates = PlayerStates::Moving;
				}
				break;
			}
		}
	}
	else
	{
		m_PlayerStates = PlayerStates::Dead;
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Blue, FString::Printf(TEXT("DEAD")));
	}
}


/// <summary>
///				This function basically clmaps all the players stats in the game.
/// 
///				This ensures that the player stats don't go lower or higher than is expected
/// </summary>
/// 
void ABase_Player::HandlePlayerStats()
{
	// health
	if (m_PlayerStats.mf_Health > m_PlayerStats.mf_MaxHealth)
	{
		m_PlayerStats.mf_Health = m_PlayerStats.mf_MaxHealth;
	}
	if (m_PlayerStats.mf_Health < 0)
	{
		m_PlayerStats.mf_Health = 0;
		m_PlayerStats.isAlive = false;
	}
	// stamina
	if (m_PlayerStats.mf_Stamina > m_PlayerStats.mf_MaxStamina)
	{
		m_PlayerStats.mf_Stamina = m_PlayerStats.mf_MaxStamina;
	}
	if (m_PlayerStats.mf_Stamina < 0)
	{
		m_PlayerStats.mf_Stamina = 0;
		mb_isDashing = false;
	}

	// move speed
	if (m_PlayerStats.mf_Movespeed < m_PlayerStats.mf_BaseMovespeed)
	{
		m_PlayerStats.mf_Movespeed = m_PlayerStats.mf_BaseMovespeed;
	}
	// strength
	if (m_PlayerStats.mf_Strength < m_PlayerStats.mf_BaseStrength)
	{
		m_PlayerStats.mf_Strength = m_PlayerStats.mf_BaseStrength;
	}
	// swing speed
	if (m_PlayerStats.mf_SwingSpeed < m_PlayerStats.mf_BaseSwingSpeed)
	{
		m_PlayerStats.mf_SwingSpeed = m_PlayerStats.mf_BaseSwingSpeed;
	}
}

void ABase_Player::InitialiseCamera()
{
	mv_CameraVec = FVector(0, 20, 40); // starting location for the camera
	mv_RangedCameraVec = FVector(0, 60, 50); // aimed location for the camera 

	mf_SpringIdleLength = 125.f; // starting length of the camera
	mf_SpringAimLength = 100.f;  // aim length for the camera

	SpringArmcomp->SocketOffset = mv_CameraVec;
	SpringArmcomp->TargetArmLength = mf_SpringIdleLength;
}

void ABase_Player::ToggleDash()
{
	if (!mb_isDashing)
	{
		if (m_PlayerStats.mf_Stamina > 0 && mb_Aiming == false)
		{
			mb_isDashing = true;
		}
	}
	else
	{
		mb_isDashing = false;
	}
}

void ABase_Player::PlayerDash(float delta)
{
	if (mb_isDashing)
	{
		m_PlayerStats.mf_Stamina -= (delta / 2);

		GetCharacterMovement()->MaxWalkSpeed = 1000.f;
		GEngine->AddOnScreenDebugMessage(-1, .01f, FColor::Yellow, TEXT("DASH"));
		mf_StaminaRegen = 0.f;
	}
	else
	{
		mf_StaminaRegen += delta;
		if (mf_StaminaRegen >= mf_StaminaTarget && m_PlayerStats.mf_Stamina < m_PlayerStats.mf_MaxStamina)
		{
			m_PlayerStats.mf_Stamina += delta;
		}
		if (mb_Aiming == false)
		{
			GetCharacterMovement()->MaxWalkSpeed = 600.f;
		}
	}
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