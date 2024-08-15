// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputData.generated.h"

/**
 * 
 */
class UInputAction;
class UInputMappingContext;
UCLASS()
class DWARF_GAME_DES310_API UInputData : public UDataAsset
{
	GENERATED_BODY()
public:
	UInputData();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs|Contexts")
	TArray<TObjectPtr<UInputMappingContext>> Contexts;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs|Movement")
	TArray<TObjectPtr<UInputAction>> MovementActions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs|Attack")
	TArray<TObjectPtr<UInputAction>> AttackActions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inputs|Misc")
	TArray<TObjectPtr<UInputAction>> MiscActions;

};
