// Fill out your copyright notice in the Description page of Project Settings.


#include "PickaxeProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Dwarf_Game_DES310/PlayerClasses/Base_Player.h"

// Sets default values
APickaxeProjectile::APickaxeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UWorld* world = GetWorld();


}

// Called when the game starts or when spawned
void APickaxeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickaxeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

