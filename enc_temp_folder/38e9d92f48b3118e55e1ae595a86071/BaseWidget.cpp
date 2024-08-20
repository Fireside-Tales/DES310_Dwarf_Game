// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetTree.h"

void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeCanvas();

	MenuIndex = 0;
	OptionsIndex = 0;

	MainMenu = NewObject<UVerticalBox>(this, TEXT("Main Menu Box"));
	if(MainMenu)
	{
		UButton* NewGameButton = NewObject<UButton>(this, TEXT("Start Game"));
		if (NewGameButton)
		{
			MainMenu->AddChild(NewGameButton);
		}
		UButton* OptionsButton = NewObject<UButton>(this, TEXT("Options"));
		if (OptionsButton)
		{
			MainMenu->AddChild(OptionsButton);
		}
		UButton* ExitButton = NewObject<UButton>(this, TEXT("Exit"));
		if (ExitButton)
		{
			MainMenu->AddChild(ExitButton);
		}
	}

}

void UBaseWidget::IncreaseMenuIndex()
{
}

void UBaseWidget::DecreaseMenuIndex()
{
}

void UBaseWidget::InitializeCanvas()
{
	if(!Canvas)
	{
		Canvas = CreateOptionalDefaultSubobject<UCanvasPanel>(TEXT("Canvas"));
		if(Canvas)
		{
			WidgetTree->RootWidget = Canvas;
		}
	}
}
