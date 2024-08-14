// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StatsComponent.h"
#include "PlayerStatsComponent.generated.h"

/**
 * 
 */
UCLASS()
class DWARF_GAME_DES310_API UPlayerStatsComponent : public UStatsComponent
{
	GENERATED_BODY()
public:
	UPlayerStatsComponent();
protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintPure)
	float GetStamina() const { return Stamina; }
	UFUNCTION(BlueprintPure)
	float GetMaxStamina() const { return MaxStamina; }

	void SetSprinting(bool Sprinting) { IsSprinting = Sprinting; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Stamina;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float MaxStamina;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float DrainRate; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float TargetTime;

	float Timer; 
	bool IsSprinting = false;

	
};
