// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent* PickMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TEnumAsByte<AxeStates> AxeState = AxeStates::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* m_Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		UAudioComponent* m_AudioComponent;


	FVector mv_InitLoc;
	FVector mv_TargLoc;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Axe Throw Stats")
		FVector mv_ImpactLoc;
	FVector mv_ImpactNormal;
	FVector mv_ThrowDir;
	FVector mv_CameraLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector mv_AxeLocationLastTick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector mv_ReturnTargetLocations;


	FRotator mr_InitRot;
	FRotator mr_CameraRot;
	FRotator mr_LodgePointRot;

	float mf_AxeThrowSpeed;
	float mf_ThrowTraceDis = 60;
	float mf_Z_Adjustment;
	float mf_MaxDistance;
	float mf_DistanceFromChar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mf_OptimalDis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mf_AxeReturnSpeed;

	float mf_AxeReturnScale;
	float mf_ReturnTilt;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float mf_AxeSpin;

	float mf_ReturnSpinRate;
	float mf_ImpulseStrength;
	float mf_AxeSpinOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float mf_SpinLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int mi_ReturnSpins;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool mb_isWiggle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool mb_Thrown;

	FName mn_BoneName;




	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ABase_Player* playerRef;

	UFUNCTION(BlueprintCallable)
		void InitialiseReturnVariables();

	UFUNCTION(BlueprintCallable)
		void InitialiseReturnTrace();

	UFUNCTION(BlueprintCallable)
		bool LineTraceMethod(FHitResult& OutHit);

	UFUNCTION(BlueprintCallable)
		bool InitSphereTrace(FHitResult& OutHit);

	UFUNCTION(BlueprintCallable)
		void ThrowAxe();
	UFUNCTION(BlueprintCallable)
		void RecallLaunched();
	UFUNCTION(BlueprintCallable)
		void LaunchAxe();

	UFUNCTION(BlueprintCallable)
		void Catch(USceneComponent* newParent);
protected:
	UFUNCTION(BlueprintCallable)
		void HandleImpact(FVector ImpactNormal, FVector ImpactLocation);
	UFUNCTION(BlueprintCallable)
		void LodgeAxe();
	UFUNCTION(BlueprintCallable)
		void AdjustAxeReturnLocation();
	UFUNCTION(BlueprintCallable)
		void AxeLodgePull(float pull);
	UFUNCTION(BlueprintCallable)
		void ReturnPosition(float rot1, float rot2, float vectorCurve, float speedCurve, USkeletalMeshComponent* skeleton);
	UFUNCTION(BlueprintCallable)
		void ReturnSpin(float TimelineSpeed);
	UFUNCTION(BlueprintCallable)
		void ReturnSpinAfterTime(float newPitch);
	UFUNCTION(BlueprintCallable)
		float AdjustAxeImpactPitch();
	UFUNCTION(BlueprintCallable)
		float GetClampedAxeDistanceFromChar(USkeletalMeshComponent* skeleton);
	UFUNCTION(BlueprintCallable)
		FVector CalculateImpulseDirection();
	UFUNCTION(BlueprintCallable)
		FVector AdjustAxeImpactLocation();
	UFUNCTION(BlueprintCallable)
		void SnapToStart();



	UFUNCTION(BlueprintCallable)
		float AdjustAxeReturnTimelineSpeed();

	UFUNCTION(BlueprintCallable)
		void InitVariables(UProjectileMovementComponent* projectileMovement, USceneComponent* pivotPoint, USceneComponent* lodgePoint, UCameraComponent* camera);
};
