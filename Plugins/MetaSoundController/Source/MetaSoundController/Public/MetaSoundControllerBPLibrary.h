// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MetaSoundControllerBPLibrary.generated.h"

/*
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu.
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UMetaSoundControllerBPLibrary : public UBlueprintFunctionLibrary
{
private:

public:

	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "MetaSoundController sample test testing"), Category = "MetaSoundController")
		static float MetaSoundControllerSampleFunction(float Param);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Metasounds Master Volume", Keywords = "Metasound Master volume setter "), Category = "MetaSoundController")
		static void SetMasterVolume(float master);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Metasounds Music Volume", Keywords = "Metasound Music volume setter "), Category = "MetaSoundController")
		static void SetMusicVolume(float music);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Metasounds Sound effects Volume", Keywords = "Metasound sound effects volume setter "), Category = "MetaSoundController")
		static void SetSoundVolume(float sfx);
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Metasounds Master Volume", Keywords = "Metasound Master volume getter "), Category = "MetaSoundController")
		static float GetMasterVolume(); 
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Metasounds Music Volume", Keywords = "Metasound music volume getter "), Category = "MetaSoundController")
		static float GetMusicVolume(); 
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Metasounds SFX Volume", Keywords = "Metasound sound effects volume getter "), Category = "MetaSoundController")
		static float GetSFXVolume(); 
};
