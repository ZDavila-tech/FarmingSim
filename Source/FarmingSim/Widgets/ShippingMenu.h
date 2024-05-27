// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractActorWidget.h"
#include "ShippingMenu.generated.h"


UCLASS()
class FARMINGSIM_API UShippingMenu : public UInteractActorWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* ShippingInven;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UInventoryGrid* WBP_PlayerGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UInventoryGrid* WBP_ShippingGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TXT_TotalEarned;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Money;

	
public:
	void NativeConstruct() override;
	void NativeDestruct() override;
	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	UFUNCTION()
	void SetMoneyEarned(int _TotalMoney);

};
