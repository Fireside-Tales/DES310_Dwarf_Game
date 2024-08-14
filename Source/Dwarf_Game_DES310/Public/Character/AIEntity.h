// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseEntity.h"
#include "AIEntity.generated.h"

/**
 *
 */
class UStatsComponent;
UCLASS()
class DWARF_GAME_DES310_API AAIEntity : public ABaseEntity
{
	GENERATED_BODY()
public:
	AAIEntity();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStatsComponent> StatsComponent;
};
