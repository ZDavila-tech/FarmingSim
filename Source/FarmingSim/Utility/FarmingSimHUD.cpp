// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingSimHUD.h"
#include "GameFramework/PlayerController.h"
#include "../Widgets/UI.h"
#include "Kismet/GameplayStatics.h"


AFarmingSimHUD::AFarmingSimHUD()
{
	PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	
}

void AFarmingSimHUD::BeginPlay()
{
	UIMenu = CreateWidget<UUI>(PC, UIClass);
	ShowUI();
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
	UIMenu->RemoveFromParent();
}
