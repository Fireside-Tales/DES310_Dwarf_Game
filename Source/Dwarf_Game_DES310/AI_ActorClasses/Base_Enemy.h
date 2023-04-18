// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_Actor.h"
#include "Base_Enemy.generated.h"

UENUM(BlueprintType)
enum EnemyStates
{
	Idle,
	Moving,
	Attacking,
	Dying,
};

UCLASS()
class DWARF_GAME_DES310_API ABase_Enemy : public AAI_Actor
{
	GENERATED_BODY()
public:
	ABase_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Enemy States)
		TEnumAsByte <EnemyStates> m_EnemyStates;

	

};
