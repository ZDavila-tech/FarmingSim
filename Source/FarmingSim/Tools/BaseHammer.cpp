// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHammer.h"
#include "../Characters/BasePlayer.h"
#include "../Animations/PlayerAnimInstance.h"

void ABaseHammer::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseHammer::Use()
{
	Super::Use();
	Player->GetPlayerAnim()->HandleFarmActions(Player->GetPlayerAnim()->SmashingAnimation);
}
