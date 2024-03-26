// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FarmingSimGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UFarmingSimGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FString> SaveSlotNames;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool AnySlots;


public:

	virtual void Init() override;

	UFUNCTION()
	bool GetAnySlots() const;
};
