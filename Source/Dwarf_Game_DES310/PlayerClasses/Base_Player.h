// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Dwarf_Game_DES310/Collectable Classes/Heirloom_Class.h"


#include "Base_Player.generated.h"


USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		bool isAlive = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float mf_MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float mf_BaseMovespeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float mf_BaseStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float mf_BaseSwingSpeed;

	float mf_Health;
	float mf_Movespeed;
	float mf_Strength;
	float mf_SwingSpeed;

};

UENUM(BlueprintType)
enum PlayerStates
{
	Idle,
	Moving,
	Attacking,
	Throwing,
	Catching,
	Dead
};

UCLASS()
class DWARF_GAME_DES310_API ABase_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABase_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StealHeirloom();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
		USpringArmComponent* SpringArmcomp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
		UCameraComponent* camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UChildActorComponent* m_Pickaxe;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = Playerstats)
		FPlayerStats m_PlayerStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = Playerstats)
		TEnumAsByte <PlayerStates> m_PlayerStates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pivots)
		USceneComponent* m_PlayerHeirloomPivot;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool mb_IsPlayerInRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool mb_HasHeirloom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AHeirloom_Class* m_heirloom;
};
