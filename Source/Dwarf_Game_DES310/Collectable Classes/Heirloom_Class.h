// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Heirloom_Class.generated.h"

UCLASS()
class DWARF_GAME_DES310_API AHeirloom_Class : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHeirloom_Class();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* m_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* Collider;
};
