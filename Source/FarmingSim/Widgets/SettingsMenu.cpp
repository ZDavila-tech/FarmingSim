// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsMenu.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "../FarmingSim.h"

USettingsMenu::USettingsMenu(const FObjectInitializer& ObjectIntializer) : Super(ObjectIntializer)
{
	if (BTN_Back == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Back Not Valid"));
	}
	if (SLIDER_Background == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Background Not Valid"));
	}
	if (SLIDER_SFX == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("SFX Not Valid"));
	}
}

void USettingsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	BTN_Back->OnClicked.AddDynamic(this, &USettingsMenu::OnBackClick);
	SLIDER_Background->OnValueChanged.AddDynamic(this, &USettingsMenu::OnBackgroundValueChange);
	SLIDER_SFX->OnValueChanged.AddDynamic(this, &USettingsMenu::OnSFXValueChange);
}

void USettingsMenu::OnBackClick()
{
	RemoveFromParent();
}

void USettingsMenu::OnSFXValueChange(float Value)
{
}

void USettingsMenu::OnBackgroundValueChange(float Value)
{
}
