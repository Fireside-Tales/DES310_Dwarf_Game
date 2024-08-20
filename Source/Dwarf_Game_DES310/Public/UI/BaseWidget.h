// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"


class UVerticalBox;
class UCanvasPanel;

/**
 *
 */
UCLASS()
class DWARF_GAME_DES310_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void IncreaseMenuIndex();
	UFUNCTION()
	void DecreaseMenuIndex();
	UFUNCTION(BlueprintCallable)
	void SelectButton();

private:
	int MenuIndex;
	int OptionsIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Menu", meta = (AllowPrivateAccess = true))
	bool IsOptions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Menu", meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<UVerticalBox> MainMenu;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Menu", meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<UVerticalBox> OptionsMenu;
	UPROPERTY(EditDefaultsOnly, Category = "Level Reference", meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UWorld> LevelRef;


};
