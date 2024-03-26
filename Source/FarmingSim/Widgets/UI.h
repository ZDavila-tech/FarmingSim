// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* BAR_Health;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* TXT_Date;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXT_Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXT_Money;

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float PercentHealth);

	UFUNCTION(BlueprintCallable)
	void SetTime();

	UFUNCTION(BlueprintCallable)
	void SetData();

};
