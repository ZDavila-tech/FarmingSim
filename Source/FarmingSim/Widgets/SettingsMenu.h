// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenu.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API USettingsMenu : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UButton* BTN_Back;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BTN_Save;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BTN_Volume;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BTN_Graphics;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerController* Player;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UWidgetSwitcher* Switch_WidgetSwitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class USaveMenu> SaveClass;

	class USaveMenu* SaveMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UVolumeMenu> VolumeClass;

	class UVolumeMenu* VolumeMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGraphicsMenu> GraphicsClass;

	class UGraphicsMenu* GraphicsMenu;

public:
	USettingsMenu(const FObjectInitializer& ObjectIntializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnBackClick();

	UFUNCTION()
	void OnSaveClick();

	UFUNCTION()
	void OnVolumeClick();

	UFUNCTION()
	void OnGraphicsClick();
	
};
