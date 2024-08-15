// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputData.h"
#include "Components/InputComponent.h"
#include "InputMappingContext.h"

UInputData::UInputData()
{
	Contexts.Add(TObjectPtr<UInputMappingContext>());
	MovementActions.Add(TObjectPtr<UInputAction>());
	AttackActions.Add(TObjectPtr<UInputAction>());
	MiscActions.Add(TObjectPtr<UInputAction>());

}
