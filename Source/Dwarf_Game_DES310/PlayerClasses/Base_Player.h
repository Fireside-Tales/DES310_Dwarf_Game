// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
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
	Aiming,
	Catching,
	Dead,
	Respawning
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
	bool mb_axeThrown = false;

		

	FVector mv_CameraVec;
	FVector mv_RangedCameraVec;
	FVector mv_desiredSocketOffset;

	float mf_CameraTurnRate;
	float mf_GamepadTurnRate;
	float mf_SpringIdleLength;
	float mf_SpringAimLength;



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

	void InitialiseCamera(); 

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
		USpringArmComponent* SpringArmcomp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
		UCameraComponent* camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UChildActorComponent* m_Pickaxe;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Playerstats)
		FPlayerStats m_PlayerStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Playerstats)
		TEnumAsByte <PlayerStates> m_PlayerStates;

	UFUNCTION(BlueprintCallable, Category = "Player Skeleton")
		USkeletalMeshComponent* GetSkeleton()
	{
		return GetMesh();
	}


};
