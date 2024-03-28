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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AFarmingSimHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class USettingsMenu> SettingsClass;

	class USettingsMenu* SettingsMenu;

public:
	UMainMenu(const FObjectInitializer& ObjectIntializer);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnNewGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnLoadGameClicked();

	UFUNCTION(BlueprintCallable)
	void OnSettingsClicked();

	UFUNCTION(BlueprintCallable)
	void OnCreditsClicked();
};
