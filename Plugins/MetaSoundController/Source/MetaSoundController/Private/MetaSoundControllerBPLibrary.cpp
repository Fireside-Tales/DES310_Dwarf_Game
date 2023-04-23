// Copyright Epic Games, Inc. All Rights Reserved.

#include "MetaSoundControllerBPLibrary.h"
#include "MetaSoundController.h"

float mf_MasterVolume = 0.5f ;
float mf_SoundEffectVolume = 0.5f ;
float mf_MusicVolume = 0.5f ;


UMetaSoundControllerBPLibrary::UMetaSoundControllerBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UMetaSoundControllerBPLibrary::MetaSoundControllerSampleFunction(float Param)
{
	return -1;
}

void UMetaSoundControllerBPLibrary::SetMasterVolume(float master)
{
	mf_MasterVolume += master; 
}

void UMetaSoundControllerBPLibrary::SetMusicVolume(float music)
{
	mf_MusicVolume = music; 
}

void UMetaSoundControllerBPLibrary::SetSoundVolume(float sfx)
{
	mf_SoundEffectVolume = sfx; 
}

float UMetaSoundControllerBPLibrary::GetMasterVolume()
{
	return mf_MasterVolume;
}

float UMetaSoundControllerBPLibrary::GetMusicVolume()
{
	return mf_MusicVolume;
}

float UMetaSoundControllerBPLibrary::GetSFXVolume()
{
	return mf_SoundEffectVolume;
}

