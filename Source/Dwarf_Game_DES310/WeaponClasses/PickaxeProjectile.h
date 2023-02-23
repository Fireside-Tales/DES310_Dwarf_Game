// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "PickaxeProjectile.generated.h"

UENUM(BlueprintType)
enum AxeStates
{
	Idle,
	Launched,
	LodgedInSomething,
	Returning
};

UCLASS()
class DWARF_GAME_DES310_API APickaxeProjectile : public ABaseWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickaxeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UProjectileMovementComponent* PickMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TEnumAsByte<AxeStates> AxeState;


	float mf_DistanceFromChar;
	FVector mv_InitLoc;
	FRotator mr_InitRot;
	FVector mv_TargLoc;
	FVector mv_ImapctLoc;
	float mf_AxeSpin;
	FVector mv_ThrowDir;
	FVector mv_CameraLoc;
	FRotator mr_CameraRot;
	float mf_OptimalDis;
	FRotator mr_LodgePointRot;
	float mf_ImpulseStrength;
	FVector mv_AxeLocationLastTick;
	float mf_AxeSpinOffset;
	float mf_AxeThrowSpeed;
	float mf_AxeReturnSpeed;
	FVector m_ImpactNormal;
	FName mn_BoneName;
	FVector mv_ReturnTargetLocations;
	int mi_ReturnSpins;
	float mf_MaxDistance;
	float mf_ReturnTilt;
	float mf_ReturnSpinRate;
	float mf_Z_Adjustment;
	bool mb_isWiggle;
	float mf_ThrowTraceDis;
	float mf_AxeReturnScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ABase_Player* playerRef;


};
