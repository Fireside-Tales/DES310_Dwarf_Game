// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamefiles/DwarfGamemode.h"
#include "Controllers/PlayerEntityController.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerStart.h>

ADwarfGamemode::ADwarfGamemode()
{
}

void ADwarfGamemode::StartNewPlayer(APlayerController* NewPlayer)
{
	APlayerEntityController* TestController = Cast<APlayerEntityController>(NewPlayer);
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts); 
	TArray<AActor*> PrefferedStarts;
	for(size_t i = 0; i < PlayerStarts.Num(); ++i)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(PlayerStarts[i]);

		if(TestController)
		{
			if(TestController->GetTeamType() == ETeamType::BlueDwarf && PlayerStart->Tags.Contains("BD"))
			{
				PrefferedStarts.Add(PlayerStart);
			}
			else if (TestController->GetTeamType() == ETeamType::RedDwarf && PlayerStart->Tags.Contains("RD"))
			{
				PrefferedStarts.Add(PlayerStart);
			}
		}
	}
	NewPlayer->SetPawn(SpawnDefaultPawnFor(NewPlayer, PrefferedStarts[FMath::RandRange(0, PrefferedStarts.Num() - 1)])); 
	RestartPlayer(NewPlayer);
}
