// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Enemy.h"



ABase_Enemy::ABase_Enemy():AAI_Actor::AAI_Actor()
{
	PrimaryActorTick.bCanEverTick = true;

}
void ABase_Enemy::BeginPlay()
{
	AAI_Actor::BeginPlay();

}

void ABase_Enemy::Tick(float DeltaTime)
{
	AAI_Actor::Tick(DeltaTime);

	if (mb_isAlive == false) 
	{
		m_EnemyStates = EnemyStates::Dying;
	}

}
