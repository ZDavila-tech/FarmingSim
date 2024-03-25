// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SettingsMenu.h"
#include "../FarmingSim.h"

UPauseMenu::UPauseMenu(const FObjectInitializer& ObjectIntializer) : Super(ObjectIntializer)
{
	if (BTN_Resume == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Resume Not Valid"));
	}
	if (BTN_Settings == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Settings Not Valid"));
	}
	if (BTN_Exit == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Exit Not Valid"));
	}

	Player = UGameplayStatics::GetPlayerController(GetWorld(),0);

	if (Player == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Player Not Valid"));
	}
	
}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	BTN_Resume->OnClicked.AddDynamic(this, &UPauseMenu::OnResumeClick);
	BTN_Settings->OnClicked.AddDynamic(this, &UPauseMenu::OnSettingsClick);
	BTN_Exit->OnClicked.AddDynamic(this, &UPauseMenu::OnExitClick);
	Player->SetPause(true);
	Player->SetInputMode(FInputModeGameAndUI());
	Player->SetShowMouseCursor(true);
}

void UPauseMenu::OnResumeClick()
{
	Player->SetPause(false);
	Player->SetShowMouseCursor(false);
	Player->SetInputMode(FInputModeGameOnly());
	RemoveFromParent();
}

void UPauseMenu::OnSettingsClick()
{
	SettingsMenu = CreateWidget<USettingsMenu>(Player, SettingsClass);
	if (SettingsMenu == nullptr)
	{
		UE_LOG(Game, Error, TEXT("Settings Menu Not Valid"));
	}
	SettingsMenu->AddToViewport();
}

void UPauseMenu::OnExitClick()
{
}
