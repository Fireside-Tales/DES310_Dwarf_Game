// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerEntity.h"
#include "Components/PlayerStatsComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"


#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "Input/InputData.h"

#include "Weapons/BaseThrowable.h"

APlayerEntity::APlayerEntity() :ABaseEntity()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateOptionalDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SocketOffset = FVector(0, 20, 40);
	SpringArm->TargetArmLength = 125;
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Camera->SetupAttachment(SpringArm);

	//Pickaxe = CreateOptionalDefaultSubobject<UChildActorComponent>(TEXT("Pickaxe"));
	//Pickaxe->SetupAttachment(GetMesh());

	PlayerStatsComponent = CreateOptionalDefaultSubobject<UPlayerStatsComponent>(TEXT("PlayerStatsComponent"));
}

void APlayerEntity::BeginPlay()
{
	Super::BeginPlay();
	if (PickaxeRef)
	{
		Pickaxe = GetWorld()->SpawnActor<ABaseThrowable>(PickaxeRef, GetActorLocation(), GetActorRotation());
		Pickaxe->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "PickaxeSocket");
	}
}

void APlayerEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		if (APlayerController* PC = Cast<APlayerController>(Controller))
		{
			if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
			{
				if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
				{
					InputSystem->ClearAllMappings(); // Clear all mappings
					// Loop through all contexts
					InputSystem->AddMappingContext(InputData->Contexts[0], 0); // Add the context to the input system
				}
			}

		}
		if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			PEI->BindAction(InputData->MovementActions[0], ETriggerEvent::Triggered, this, &APlayerEntity::Move);
			PEI->BindAction(InputData->MovementActions[1], ETriggerEvent::Triggered, this, &APlayerEntity::RotateCamera);
		}
	}
}

void APlayerEntity::Move(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();
	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), Movement.Y);
		AddMovementInput(GetActorRightVector(), Movement.X);
	}
}

void APlayerEntity::RotateCamera(const FInputActionValue& Value)
{
	FVector2D Rotate = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerPitchInput(Rotate.Y);
		AddControllerYawInput(Rotate.X);
	}

}
