// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "../FarmingSimGameInstance.h"
#include "../FarmingSim.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectIntializer) : Super(ObjectIntializer)
{
	if (BTN_LoadGame == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Load Game Not Valid"));
	}
	if (BTN_NewGame == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("New Game Not Valid"));
	}
	if (BTN_Settings == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Settings Button Not Valid"));
	}
	if (BTN_Credits == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Credits Button Not Valid"));
	}

	
}

void UMainMenu::NativeConstruct()
{
	GameInstance = Cast<UFarmingSimGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("Game Instance Not Valid"));
		return;
	}

	if (!GameInstance->GetAnySlots())
	{
		if (BTN_LoadGame)
		{
			BTN_LoadGame->SetIsEnabled(false);
		}
		
	}
}
