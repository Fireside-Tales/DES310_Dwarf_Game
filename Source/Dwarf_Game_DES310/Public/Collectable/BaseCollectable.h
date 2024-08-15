// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCollectable.generated.h"


class UCapsuleComponent;
class UBounceRotationComponent;
UCLASS()
class DWARF_GAME_DES310_API ABaseCollectable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseCollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Meshes", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCapsuleComponent> Collider;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rotation", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBounceRotationComponent> Rotator; 
};
