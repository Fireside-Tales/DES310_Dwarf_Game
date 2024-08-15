// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseThrowable.generated.h"


class UProjectileMovementComponent;

UCLASS()
class DWARF_GAME_DES310_API ABaseThrowable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseThrowable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
#pragma region Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Pivot", meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> PivotPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Pivot", meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> LodgePoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Movement", meta = (AllowPrivateAccess = true))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components|Audio", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAudioComponent> AudioComponent;
#pragma endregion

#pragma region Variables
	FVector InitLoc;
	FVector TargLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Throw Stats",meta = (AllowPrivateAccess = true))
	FVector ImpactLoc;
	FVector ImpactNormal;
	FVector ThrowDir;
	FVector CameraLoc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Throw Stats",meta = (AllowPrivateAccess = true))
	FVector AxeLocationLastTick;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Throw Stats",meta = (AllowPrivateAccess = true))
	FVector ReturnTargetLocations;

#pragma endregion

#pragma region Functions
	UFUNCTION()
	void OnOverLapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
