// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingSimHUD.h"
#include "GameFramework/PlayerController.h"
#include "../Widgets/UI.h"
#include "../Characters/DayNightCycle.h"
#include "Kismet/GameplayStatics.h"
#include "../Widgets/MainMenu.h"


AFarmingSimHUD::AFarmingSimHUD()
{
	PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	
}

void AFarmingSimHUD::BeginPlay()
{
	UIMenu = CreateWidget<UUI>(PC, UIClass);

	MainMenu = CreateWidget<UMainMenu>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MainMenuClass);
	if (MainMenu != nullptr && UGameplayStatics::GetCurrentLevelName(GetWorld()) == FName("Map_MainMenu"))
	{
		MainMenu->AddToViewport();
	}
	else
	{
		MainMenu->RemoveFromParent();
		ShowUI();
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DayNightClass, OutActor);
	Cast<ADayNightCycle>(OutActor[0])->GetDateDelegate()->AddDynamic(UIMenu, &UUI::SetDate);
	Cast<ADayNightCycle>(OutActor[0])->GetTimeDelegate()->AddDynamic(UIMenu, &UUI::SetTime);
}

void AFarmingSimHUD::ShowUI()
{
	if (UIMenu)
	{
		UIMenu->AddToViewport();
	}
}

void AFarmingSimHUD::HideUI()
{
	if (UIMenu != nullptr)
	{
		UIMenu->RemoveFromParent();
	}
}

UUI* AFarmingSimHUD::GetUI()
{
	return UIMenu;
}

void AFarmingSimHUD::EnterMenuMode()
{
	PC->SetInputMode(FInputModeGameAndUI());
	PC->SetShowMouseCursor(true);
}

void AFarmingSimHUD::ExitMenuMode()
{
	PC->SetShowMouseCursor(false);
	PC->SetInputMode(FInputModeGameOnly());
}
