// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
//#include "Blueprint/UserWidget.h"
#include "Dwarf_Game_DES310/Collectable Classes/Heirloom_Class.h"

#include "EngineUtils.h"

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
		float mf_MaxStamina;
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
	float mf_Stamina;

};

UENUM(BlueprintType)
enum class PlayerStates :uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Moving UMETA(DisplayName = "Moving"),
	Attacking UMETA(DisplayName = "Attacking"),
	Throwing UMETA(DisplayName = "Throwing"),
	Aiming UMETA(DisplayName = "Aiming"),
	Catching UMETA(DisplayName = "Catching"),
	Dead UMETA(DisplayName = "Dead"),
	Respawning UMETA(DisplayName = "Respawning"),
	Emote UMETA(DisplayName = "Emote")
};

UENUM(BlueprintType)
enum class PlayerAttacks :uint8
{
	None UMETA(DisplayName = "None"),
	Light1 UMETA(DisplayName = "Light1"),
	Light2 UMETA(DisplayName = "Light2"),
	Light3 UMETA(DisplayName = "Light3"),
	Heavy1 UMETA(DisplayName = "Heavy1"),
	Heavy2 UMETA(DisplayName = "Heavy2"),
	Heavy3 UMETA(DisplayName = "Heavy3")
};
UENUM(BlueprintType)
enum class PlayerEmotes :uint8
{
	Emote1 UMETA(DisplayName = "Emote1"),
	Emote2 UMETA(DisplayName = "Emote2"),
	Emote3 UMETA(DisplayName = "Emote3"),
	Emote4 UMETA(DisplayName = "Emote4")
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

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Types")
	//	TSubclassOf<UUserWidget> m_Widget;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	UUserWidget* m_AimHud;

	bool mb_UseContRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axe Throw")
		bool mb_Aiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Axe Throw")
		class APickaxeProjectile* m_AxeRef;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		FVector mv_CameraVec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		FVector mv_RangedCameraVec;
	FVector mv_desiredSocketOffset;

	float mf_CameraTurnRate;
	float mf_GamepadTurnRate;
	float mf_SpringIdleLength;
	float mf_SpringAimLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool mb_isDashing;
	float mf_StaminaRegen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		float mf_StaminaTarget;




	UFUNCTION(BlueprintCallable, Category = "Axe Throw")
		void Aim();
	UFUNCTION(BlueprintCallable, Category = "Axe Throw")
		void ReleaseAim();
	UFUNCTION(BlueprintCallable, Category = "Axe Throw")
		void ThrowAxe();
	UFUNCTION(BlueprintCallable, Category = "Axe Throw")
		void SetSocketOffset(float input);
	UFUNCTION(BlueprintCallable, Category = "Axe Throw")
		void LerpCamera(float alpha);

	UFUNCTION(BlueprintCallable, Category = "Player States")
		void HandlePlayerStates();
	UFUNCTION(BlueprintCallable, Category = "Player Stats")
		void HandlePlayerStats();


	void ThrowInput();
	void LightAttackInput();
	void HeavyAttackInput();

	void FirstEmote()
	{
		m_PlayerStates = PlayerStates::Emote;
		m_PlayerEmotes = PlayerEmotes::Emote1;
	}
	void SecondEmote()
	{
		m_PlayerStates = PlayerStates::Emote;
		m_PlayerEmotes = PlayerEmotes::Emote2;
	}
	void ThirdEmote()
	{
		m_PlayerStates = PlayerStates::Emote;
		m_PlayerEmotes = PlayerEmotes::Emote3;
	}
	void ForthEmote()
	{
		m_PlayerStates = PlayerStates::Emote;
		m_PlayerEmotes = PlayerEmotes::Emote4;
	}

	void HandleAttacks();

	void InitialiseCamera();

	void EnableDash();
	void DisableDash(); 

	UFUNCTION(BlueprintCallable)
		void PlayerDash(float delta);

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Playerstats)
		FPlayerStats m_PlayerStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Playerstates)
		TEnumAsByte <PlayerStates> m_PlayerStates;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Playerstates)
		TEnumAsByte<PlayerAttacks> m_CurrentAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Playerstates)
		bool mb_AttackFinished;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Playerstates)
		TEnumAsByte <PlayerEmotes> m_PlayerEmotes;

	TQueue<TEnumAsByte<PlayerAttacks>> m_NextAttack;


	UFUNCTION(BlueprintCallable, Category = "Player Skeleton")
		USkeletalMeshComponent* GetSkeleton()
	{
		return GetMesh();
	}


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pivots)
		USceneComponent* m_PlayerHeirloomPivot;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool mb_IsPlayerInRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool mb_HasHeirloom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AHeirloom_Class* m_heirloom;

	UFUNCTION(BlueprintCallable)
		void ReduceHealth(float h)
	{
		m_PlayerStats.mf_Health -= h;
	}
	UFUNCTION(BlueprintCallable)
		float GetStaminaPercentage()
	{
		return m_PlayerStats.mf_Stamina / m_PlayerStats.mf_MaxStamina;
	}
	UFUNCTION(BlueprintCallable)
		float GetHealthPercentage()
	{
		return m_PlayerStats.mf_Health / m_PlayerStats.mf_MaxHealth;
	}

	UFUNCTION(BlueprintCallable)
		void DamagePlayer(float damage)
	{
		m_PlayerStats.mf_Health -= damage;
	}
	UFUNCTION(BlueprintCallable)
		void RespawnPlayer()
	{
		m_PlayerStats.mf_Health = m_PlayerStats.mf_MaxHealth;
		m_PlayerStats.isAlive = true;
		for (TActorIterator<AHeirloom_Class> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			m_heirloom = *ActorItr;
		}
	}
};
