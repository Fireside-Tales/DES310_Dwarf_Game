// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseThrowable.generated.h"


class UProjectileMovementComponent;
class UDamageComponent;
class APlayerEntity;
class USkeletalMeshComponent;

UENUM()
enum class EAxeStates : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Launched	UMETA(DisplayName = "Launched"),
	Lodged		UMETA(DisplayName = "Lodged"),
	Returning	UMETA(DisplayName = "Returning"),
};
UCLASS()
class DWARF_GAME_DES310_API ABaseThrowable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseThrowable();

	void Recall();
	void Catch(USceneComponent* newParent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	void InitialiseReturnVariables();

	UFUNCTION(BlueprintPure)
	float AdjustAxeReturnTimelineSpeed();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartAxeSpin();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopAxeSpin();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartReturnSpin(float speed);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopReturnSpin();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopAxeMovement();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopReturnTrace();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartReturnTrace();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LineTraceTimeline();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopTrace();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReturnPositionTimeline();
	UFUNCTION(BlueprintImplementableEvent)
	void RecallEvent();


	UFUNCTION(BlueprintPure)
	bool LineTrace(FHitResult& OutHit);
	UFUNCTION(BlueprintPure)
	bool InitSphere(FHitResult& OutHit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetIsThrown() { return isThrown; }

	void SetPlayerRef(APlayerEntity* newPlayer) { PlayerRef = newPlayer; }
private:
#pragma region Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Pivot", meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> PivotPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Pivot", meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> LodgePoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Pivot", meta = (AllowPrivateAccess = true))
	TObjectPtr <USkeletalMeshComponent>Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Movement", meta = (AllowPrivateAccess = true))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Audio", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Audio", meta = (AllowPrivateAccess = true))
	TObjectPtr<UDamageComponent> DamageComponent;
#pragma endregion

#pragma region Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = true))
	TObjectPtr<APlayerEntity> PlayerRef;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = true))
	EAxeStates AxeState = EAxeStates::Idle;

	FVector InitLoc;
	FVector TargLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw Stats|Positions", meta = (AllowPrivateAccess = true))
	FVector ImpactLoc;
	FVector ImpactNormal;
	FVector ThrowDir;
	FVector CameraLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw Stats|Positions", meta = (AllowPrivateAccess = true))
	FVector AxeLocationLastTick;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Throw Stats|Positions", meta = (AllowPrivateAccess = true))
	FVector ReturnTargetLocations;

	FRotator InitRot;
	FRotator CameraRot;
	FRotator LodgePointRot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw Stats|Speed", meta = (AllowPrivateAccess = true))
	float AxeThrowSpeed;
	float ThrowTraceDis = 60;
	float Z_Adjustment;
	float MaxDistance;
	float DistanceFromChar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw Stats|Distance", meta = (AllowPrivateAccess = true))
	float OptimalDis;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw Stats|Speed", meta = (AllowPrivateAccess = true))
	float AxeReturnSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw Stats| Distance", meta = (AllowPrivateAccess = true))
	float AxeReturnScale;
	float ReturnTilt;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw Stats|Distance", meta = (AllowPrivateAccess = true))
	float AxeSpin;

	float ReturnSpinRate;
	float ImpulseStrength;
	float AxeSpinOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw Stats|Distance", meta = (AllowPrivateAccess = true))
	float SpinLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Throw Stats|Distance", meta = (AllowPrivateAccess = true))
	int ReturnSpins;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw Stats|Distance", meta = (AllowPrivateAccess = true))
	bool isWiggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw Stats|Distance", meta = (AllowPrivateAccess = true))
	bool isThrown;

	FName BoneName;

#pragma endregion

#pragma region Functions
	UFUNCTION()
	void OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void InitialiseReturnTrace();


	bool LineTraceMethod(FHitResult& OutHit);
	bool InitSphereTrace(FHitResult& OutHit);

	UFUNCTION(BlueprintCallable)
	void ThrowAxe();
	void RecallLaunched();
	void LaunchAxe();

	UFUNCTION(BlueprintCallable)
	void HandleImpact(FVector ImpactNormal, FVector ImpactLocation);
	UFUNCTION(BlueprintCallable)
	void LodgeAxe();
	void AdjustAxeReturnLocation();
	void AxeLodgePull(float pull);
	UFUNCTION(BlueprintCallable)
	void ReturnPosition(float rot1, float rot2, float vectorCurve, float speedCurve, USkeletalMeshComponent* skeleton);
	UFUNCTION(BlueprintCallable)
	void ReturnSpin(float TimelineSpeed);
	UFUNCTION(BlueprintCallable)
	void ReturnSpinAfterTime(float newPitch);
	float GetClampedAxeDistanceFromChar(USkeletalMeshComponent* skeleton);
	FVector CalculateImpulseDirection();
	FVector AdjustAxeImpactLocation();
	void SnapToStart();

	float AdjustAxeImpactPitch();

#pragma endregion
};
