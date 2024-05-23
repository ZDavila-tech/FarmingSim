// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShippingMenu.generated.h"


UCLASS()
class FARMINGSIM_API UShippingMenu : public UUserWidget
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
	class APlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABasePlayer* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey ExitButton;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	UFUNCTION()
	void SetMoneyEarned(int _TotalMoney);

};
