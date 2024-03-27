// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingSimHUD.h"
#include "GameFramework/PlayerController.h"
#include "../Widgets/UI.h"
#include "Kismet/GameplayStatics.h"
#include "../Widgets/MainMenu.h"


AFarmingSimHUD::AFarmingSimHUD()
{
	PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	
}

void AFarmingSimHUD::BeginPlay()
{
	UIMenu = CreateWidget<UUI>(PC, UIClass);
	ShowUI();

	/*MainMenu = CreateWidget<UMainMenu>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MainMenuClass);
	if (MainMenu != nullptr)
	{
		MainMenu->AddToViewport();
	}*/
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
