// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_Actor.h"
#include "Base_Enemy.generated.h"

UENUM(BlueprintType)
enum class EnemyStates:uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Moving UMETA(DisplayName = "Moving"),
	Attacking UMETA(DisplayName = "Attacking"),
	Dying UMETA(DisplayName = "Dying"),
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EnemyStates m_EnemyStates;

public: 
	virtual void Tick(float DeltaTime) override;
	

};
