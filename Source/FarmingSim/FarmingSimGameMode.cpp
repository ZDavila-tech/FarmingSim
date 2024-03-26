// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingSimGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/FarmingSimHUD.h"


void AFarmingSimGameMode::BeginPlay()
{
	HUD = Cast<AFarmingSimHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	
}
