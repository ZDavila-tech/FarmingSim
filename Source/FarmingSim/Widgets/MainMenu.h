// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* BTN_LoadGame;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTN_NewGame;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTN_Settings;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTN_Credits;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UFarmingSimGameInstance* GameInstance;

public:
	UMainMenu(const FObjectInitializer& ObjectIntializer);

	virtual void NativeConstruct() override;
};
