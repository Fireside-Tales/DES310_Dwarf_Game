// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Collectable.generated.h"

UENUM(BlueprintType)
enum CollectibleType
{
	Health = 0,
	MaxHealth,
	SwingSpeed,
	MoveSpeed,
	Strength
};

UCLASS()
class DWARF_GAME_DES310_API ABase_Collectable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABase_Collectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	float mf_yawRotation;
	float mf_yOffset;
	bool mb_Bounce;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* m_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* Collider;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float rotationSpeed;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float bounceSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float mf_CollectValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
		TEnumAsByte<CollectibleType> m_CollectibleType;

};
