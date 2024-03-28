// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSave.h"
#include "FarmingSimSaveGame.generated.h"


/**
 * 
 */
UCLASS()
class FARMINGSIM_API UFarmingSimSaveGame : public USaveGame
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPlayerSave PlayerData;

};
