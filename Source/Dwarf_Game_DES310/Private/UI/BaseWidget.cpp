// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetTree.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MenuIndex = 0;
	OptionsIndex = 0;
	IsOptions = false;


}
void UBaseWidget::IncreaseMenuIndex()
{
	if (IsOptions)
	{

	}
	else
	{
		MenuIndex++;
		if (MenuIndex > MainMenu->GetAllChildren().Num())
		{
			MenuIndex = 0;
		}
	}
}

void UBaseWidget::DecreaseMenuIndex()
{
	if (IsOptions)
	{

	}
	else
	{
		MenuIndex--;
		if (MenuIndex < 0)
		{
			MenuIndex = MainMenu->GetAllChildren().Num();
		}
	}
}

void UBaseWidget::SelectButton()
{
	if(IsOptions == false)
	{
		switch(MenuIndex)
		{
		case 0:
			if(LevelRef)
			{
				UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(),LevelRef);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Level Reference is not set"));
			}
			break; 
		case 1:
			IsOptions = true;
			break;
		case 2:
			UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
			break;
		default:
			break; 
		}
	}
	else 
	{
		//switch(OptionsIndex)
		//{
		//	
		//}
	}
}

