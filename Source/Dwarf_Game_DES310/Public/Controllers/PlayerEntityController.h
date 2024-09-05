// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerEntityController.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETeamType : uint8
{
	RedDwarf UMETA(DisplayName = "Red"),
	BlueDwarf UMETA(DisplayName = "Blue"),

};

UCLASS()
class DWARF_GAME_DES310_API APlayerEntityController : public APlayerController
{
	GENERATED_BODY()
public:
	APlayerEntityController();

	ETeamType GetTeamType() const { return TeamType; }
	UFUNCTION(BlueprintCallable)
	void SetTeamType(ETeamType NewTeamType) { TeamType = NewTeamType; }

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Team", meta = (AllowPrivateAccess = true))
	ETeamType TeamType;
};
