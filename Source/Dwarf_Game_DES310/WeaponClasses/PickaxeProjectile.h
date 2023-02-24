// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "PickaxeProjectile.generated.h"

UENUM(BlueprintType)
enum class AxeStates : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Launched	UMETA(DisplayName = "Launched"),
	Lodged		UMETA(DisplayName = "Lodged"),
	Returning	UMETA(DisplayName = "Returning"),
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
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
		TEnumAsByte<AxeStates> AxeState = AxeStates::Idle;

	FVector mv_InitLoc;
	FVector mv_TargLoc;
	FVector mv_ImapctLoc;
	FVector m_ImpactNormal;
	FVector mv_ThrowDir;
	FVector mv_CameraLoc;
	FVector mv_AxeLocationLastTick;
	FVector mv_ReturnTargetLocations;


	FRotator mr_InitRot;
	FRotator mr_CameraRot;
	FRotator mr_LodgePointRot;

	float mf_AxeThrowSpeed;
	float mf_ThrowTraceDis;
	float mf_Z_Adjustment;
	float mf_MaxDistance;
	float mf_DistanceFromChar;
	float mf_OptimalDis;
	float mf_AxeReturnSpeed;
	float mf_AxeReturnScale;
	float mf_ReturnTilt;
	float mf_AxeSpin;
	float mf_ReturnSpinRate;
	float mf_ImpulseStrength;
	float mf_AxeSpinOffset;


	int mi_ReturnSpins;
	
	bool mb_isWiggle;
	bool mb_Thrown;

	FName mn_BoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ABase_Player* playerRef;


protected:
	void ThrowAxe();
	void RecallLaunched();
	void LaunchAxe();
	void Catch(USceneComponent* newParent); 
	void HandleImpact(FVector ImpactNormal, FVector ImpactLocation);
	void LodgeAxe();
	void AdjustAxeReturnLocation();
	void AxeLodgePull(float pull);
	void ReturnPosition(float rot1, float rot2, float vectorCurve, float speedCurve, USkeletalMeshComponent* skeleton); 
	void ReturnSpin(float TimelineSpeed);
	void ReturnSpineAfterTime(float newPitch);
	float AdjustAxeImpactPitch();
	float GetClampedAxeDistanceFromChar(USkeletalMeshComponent* skeleton);
	FVector CalculateImpulseDirection();
	FVector AdjustAxeImpactLocation();

	void SnapToStart();

	float AdjustAxeReturnTimelineSpeed(float OptimalDistance, float AxeReturnSpeed);

};
