// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DwarfGamemode.generated.h"

/**
 * 
 */
UCLASS()
class DWARF_GAME_DES310_API ADwarfGamemode : public AGameModeBase
{
	GENERATED_BODY()
public: 
	ADwarfGamemode();

	UFUNCTION(BlueprintCallable)
	virtual void StartNewPlayer(APlayerController* NewPlayer);
};
