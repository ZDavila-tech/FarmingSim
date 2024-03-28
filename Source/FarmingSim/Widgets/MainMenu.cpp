// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "../FarmingSimGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Utility/FarmingSimHUD.h"
#include "SettingsMenu.h"
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
	
	HUD = Cast<AFarmingSimHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (HUD == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("HUD Not Valid"));
		return;
	}

	BTN_NewGame->OnClicked.AddDynamic(this, &UMainMenu::OnNewGameClicked);
	BTN_LoadGame->OnClicked.AddDynamic(this, &UMainMenu::OnLoadGameClicked);
	BTN_Settings->OnClicked.AddDynamic(this, &UMainMenu::OnSettingsClicked);
	BTN_Credits->OnClicked.AddDynamic(this, &UMainMenu::OnCreditsClicked);

	if (!GameInstance->GetAnySlots())
	{
		if (BTN_LoadGame)
		{
			BTN_LoadGame->SetIsEnabled(false);
		}
	}
}

void UMainMenu::OnNewGameClicked()
{	
	UGameplayStatics::OpenLevel(GetWorld(), FName("ThirdPersonMap"));
}

void UMainMenu::OnLoadGameClicked()
{
}

void UMainMenu::OnSettingsClicked()
{
	SettingsMenu = CreateWidget<USettingsMenu>(UGameplayStatics::GetPlayerController(GetWorld(), 0), SettingsClass);
	if (SettingsMenu == nullptr)
	{
		UE_LOG(Game, Error, TEXT("Settings Menu Not Valid"));
	}
	SettingsMenu->AddToViewport();
	SettingsMenu->bIsFocusable = true;
}

void UMainMenu::OnCreditsClicked()
{
}
