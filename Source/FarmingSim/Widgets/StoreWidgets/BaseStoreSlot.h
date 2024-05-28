// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseStoreSlot.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UBaseStoreSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	FText Name;
	float price;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TXT_ItemName;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TXT_Price;
	UPROPERTY(EditDefaultsOnly)
	class UDataTable* ItemDataTable;
public:
	virtual void NativeConstruct() override;
};
