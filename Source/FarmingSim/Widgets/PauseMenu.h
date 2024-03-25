// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FARMINGSIM_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UButton* BTN_Resume;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BTN_Settings;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BTN_Exit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerController* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class USettingsMenu> SettingsClass;

	class USettingsMenu* SettingsMenu;

public:
	UPauseMenu(const FObjectInitializer& ObjectIntializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnResumeClick();

	UFUNCTION()
	void OnSettingsClick();

	UFUNCTION()
	void OnExitClick();
};
