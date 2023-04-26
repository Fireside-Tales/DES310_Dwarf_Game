// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Collectable.h"
#include "Heirloom_Class.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class DWARF_GAME_DES310_API AHeirloom_Class : public ABase_Collectable
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
	UFUNCTION(BlueprintCallable)
		void SnapToPlayer(USceneComponent* dwarfHeirloomPivot, AActor* player);

	UFUNCTION(BlueprintCallable)
		void NullPlayerRef();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pivots)
		USceneComponent* m_HeirloomPivot;

	AActor* m_PlayerRef;


};
