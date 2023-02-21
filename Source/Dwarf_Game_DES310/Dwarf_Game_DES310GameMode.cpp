// Copyright Epic Games, Inc. All Rights Reserved.

#include "Dwarf_Game_DES310GameMode.h"
#include "Dwarf_Game_DES310Character.h"
#include "UObject/ConstructorHelpers.h"

ADwarf_Game_DES310GameMode::ADwarf_Game_DES310GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/Player_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
