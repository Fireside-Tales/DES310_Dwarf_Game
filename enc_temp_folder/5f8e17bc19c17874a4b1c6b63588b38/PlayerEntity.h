// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseEntity.h"
#include "PlayerEntity.generated.h"

/**
 *
 */
class UPlayerStatsComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputData;
class ABaseThrowable;

UCLASS()
class DWARF_GAME_DES310_API APlayerEntity : public ABaseEntity
{
	GENERATED_BODY()
public:

	APlayerEntity();
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void LerpCamera();
	UFUNCTION(BlueprintCallable)
	void LerpCameraAlpha(float Alpha);


public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	TObjectPtr<UCameraComponent> GetCamera() { return Camera; }
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	TObjectPtr<UPlayerStatsComponent> PlayerStatsComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputData> InputData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TObjectPtr<ABaseThrowable> Pickaxe;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TSubclassOf<ABaseThrowable> PickaxeRef;

#pragma region Functions

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void RotateCamera(const FInputActionValue& Value);

	UFUNCTION()
	void Aim();
	UFUNCTION()
	void ReleaseAim();


	UFUNCTION()
	void ThrowAxe();

	UFUNCTION(BlueprintCallable)
	void Catch();
	UFUNCTION(BlueprintCallable)
	void Recall();

	UFUNCTION()
	void StartDash();
	UFUNCTION()
	void StopDash();

#pragma endregion

	UPROPERTY(BlueprintReadOnly, Category = "Axe Stats", meta = (AllowPrivateAccess = true))
	bool isAiming;
	UPROPERTY(BlueprintReadWrite, Category = "Axe Stats", meta = (AllowPrivateAccess = true))
	bool isThrowing;

	bool isDashing;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))

	float IdleLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))

	float AimLength;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	FVector IdleVec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	FVector AimVec;

	FVector desiredSocketOffset;

};
