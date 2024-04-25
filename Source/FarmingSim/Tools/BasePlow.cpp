// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlow.h"
#include "../Characters/BasePlayer.h"
#include "../Animations/PlayerAnimInstance.h"

void ABasePlow::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePlow::Use()
{
	Super::Use();
	Player->GetPlayerAnim()->HandleFarmActions(Player->GetPlayerAnim()->PlowingAnimation);
}

