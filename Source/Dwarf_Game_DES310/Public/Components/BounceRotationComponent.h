// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "BounceRotationComponent.generated.h"

/**
 * 
 */
UCLASS()
class DWARF_GAME_DES310_API UBounceRotationComponent : public URotatingMovementComponent
{
	GENERATED_BODY()
public:
	UBounceRotationComponent();

protected:
	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bounce", meta = (AllowPrivateAccess = true))
	float Time;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bounce", meta = (AllowPrivateAccess = true))
	float BounceSpeed;


	FVector StartLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bounce", meta =(AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> BounceTarget;
	
};
