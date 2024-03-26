// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FarmingSimHUD.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API AFarmingSimHUD : public AHUD
{
	GENERATED_BODY()
protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUI> UIClass;

	class UUI* UIMenu;

public:
	
	AFarmingSimHUD();

	UFUNCTION()
	void ShowUI();

	UFUNCTION()
	void HideUI();
};
