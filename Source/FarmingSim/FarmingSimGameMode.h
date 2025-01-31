// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FarmingSimGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API AFarmingSimGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AFarmingSimHUD* HUD;


};
