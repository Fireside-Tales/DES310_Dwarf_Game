// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameraSensitivityBPLibrary.h"
#include "CameraSensitivity.h"

float Horizontal = 30.f;
float Vertical = 30.f;

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
