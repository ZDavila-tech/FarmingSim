// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/SaveInterface.h"
#include "FarmingSimGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UFarmingSimGameInstance : public UGameInstance, public ISaveInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FString> SaveSlotNames;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool AnySlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFarmingSimSaveGame* SaveData;


public:

	virtual void Init() override;

	UFUNCTION()
	bool GetAnySlots() const;

	void LoadGameData() override;

	void SaveGameData(bool isAsync) override;

	UFarmingSimSaveGame* GetGameData() override;

	void SavePlayerData(FPlayerSave playerInfo) override;
};
