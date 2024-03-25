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
	class USlider* SLIDER_Background;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USlider* SLIDER_SFX;

public:
	USettingsMenu(const FObjectInitializer& ObjectIntializer);

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnBackClick();

	UFUNCTION()
	void OnSFXValueChange(float Value);

	UFUNCTION()
	void OnBackgroundValueChange(float Value);
	
};
