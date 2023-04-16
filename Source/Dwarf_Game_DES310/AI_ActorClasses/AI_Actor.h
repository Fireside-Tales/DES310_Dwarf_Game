// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_Actor.generated.h"

UCLASS()
class DWARF_GAME_DES310_API AAI_Actor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAI_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float mf_health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool mb_isAlive;


};
