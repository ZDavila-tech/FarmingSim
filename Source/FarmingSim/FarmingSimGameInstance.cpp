// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingSimGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/PlayerSave.h"

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

	LoadGameData();
}

bool UFarmingSimGameInstance::GetAnySlots() const
{
	return AnySlots;
}

void UFarmingSimGameInstance::LoadGameData()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName,0))
	{
		SaveData = Cast<UFarmingSimSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	}
	else
	{
		SaveData = Cast<UFarmingSimSaveGame>(UGameplayStatics::CreateSaveGameObject(TSubclassOf<USaveGame>()));
	}
}

void UFarmingSimGameInstance::SaveGameData(bool isAsync)
{
	UGameplayStatics::SaveGameToSlot(SaveData, SaveSlotName, 0);
}

UFarmingSimSaveGame* UFarmingSimGameInstance::GetGameData()
{
	return SaveData;
}

void UFarmingSimGameInstance::SavePlayerData(FPlayerSave playerInfo)
{
	SaveGameData(false);
}
