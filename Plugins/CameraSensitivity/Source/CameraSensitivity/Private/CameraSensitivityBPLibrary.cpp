// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameraSensitivityBPLibrary.h"
#include "CameraSensitivity.h"

float Horizontal = 0.5f;
float Vertical = 0.5f;

UCameraSensitivityBPLibrary::UCameraSensitivityBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UCameraSensitivityBPLibrary::HorizontalSensitivity(float Sensitivity)
{
	Horizontal = Sensitivity;
}

void UCameraSensitivityBPLibrary::VerticalSensitivity(float Sensitivity)
{
	Vertical = Sensitivity;
}

float UCameraSensitivityBPLibrary::GetHorizontalSensitivity()
{
	return Horizontal;
}

float UCameraSensitivityBPLibrary::GetVerticalSensitivity()
{
	return Vertical;
}
