// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingSimGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UFarmingSimGameInstance::Init()
{
	if (SaveSlotNames.IsEmpty())
	{
		AnySlots = false;
	}
	else
	{
		AnySlots = true;
	}
}

bool UFarmingSimGameInstance::GetAnySlots() const
{
	return AnySlots;
}
