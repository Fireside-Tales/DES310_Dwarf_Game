// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectable/BaseCollectable.h"
#include "Heirloom.generated.h"

class APlayerEntity;
UCLASS()
class DWARF_GAME_DES310_API AHeirloom : public ABaseCollectable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHeirloom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pivots", meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> HeirloomPivot;


	TObjectPtr<AActor> PlayerRef;

	void SnapToPlayer(APlayerEntity* player);

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
