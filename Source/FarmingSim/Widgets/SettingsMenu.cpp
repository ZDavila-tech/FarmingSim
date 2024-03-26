// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsMenu.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/WidgetSwitcher.h"
#include "SaveMenu.h"
#include "VolumeMenu.h"
#include "GraphicsMenu.h"
#include "Kismet/GameplayStatics.h"
#include "../FarmingSim.h"

USettingsMenu::USettingsMenu(const FObjectInitializer& ObjectIntializer) : Super(ObjectIntializer)
{
	if (BTN_Back == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Back Not Valid"));
	}
	if (BTN_Save == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Save Menu Not Valid"));
	}
	if (BTN_Volume == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Volume Menu Not Valid"));
	}
	if (BTN_Graphics == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Graphics Menu Not Valid"));
	}
	if (Switch_WidgetSwitch == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Switcher Not Valid"));
	}

	Player = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (Player == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Player Not Valid"));
	}
}

void USettingsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	BTN_Back->OnClicked.AddDynamic(this, &USettingsMenu::OnBackClick);
	BTN_Save->OnClicked.AddDynamic(this, &USettingsMenu::OnSaveClick);
	BTN_Volume->OnClicked.AddDynamic(this, &USettingsMenu::OnVolumeClick);
	BTN_Graphics->OnClicked.AddDynamic(this, &USettingsMenu::OnGraphicsClick);

	SaveMenu = CreateWidget<USaveMenu>(Player, SaveClass);
	if (SaveMenu == nullptr)
	{
		UE_LOG(Game, Error, TEXT("Save Menu Not Valid"));
	}
	VolumeMenu = CreateWidget<UVolumeMenu>(Player, VolumeClass);
	if (VolumeMenu == nullptr)
	{
		UE_LOG(Game, Error, TEXT("Volume Menu Not Valid"));
	}
	GraphicsMenu = CreateWidget<UGraphicsMenu>(Player, GraphicsClass);
	if (GraphicsMenu == nullptr)
	{
		UE_LOG(Game, Error, TEXT("Graphics Menu Not Valid"));
	}
}

void USettingsMenu::OnBackClick()
{
	RemoveFromParent();
}

void USettingsMenu::OnSaveClick()
{
	Switch_WidgetSwitch->SetActiveWidgetIndex(0);
}

void USettingsMenu::OnVolumeClick()
{
	Switch_WidgetSwitch->SetActiveWidgetIndex(1);
}

void USettingsMenu::OnGraphicsClick()
{
	Switch_WidgetSwitch->SetActiveWidgetIndex(2);
}

