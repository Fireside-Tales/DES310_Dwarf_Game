// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Procedural_Room.generated.h"//generates have to go last


UCLASS()
class DWARF_GAME_DES310_API AProcedural_Room : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcedural_Room();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Ability)//first argument says you can call into the blueprint, the category groups variables into different folders by categories. Categories are local to the class
	void KillPlayer();

	UFUNCTION(BlueprintCallable, Category = Ability)//first argument says you can call into the blueprint, the category groups variables into different folders by categories. Categories are local to the class
	void KillPlayerWithTimer(float time);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStat);//first argument is how to access it when editing, second argument gives it getters and setters, third is categories
	float health;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
