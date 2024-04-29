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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* BOX_EquipmentGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UInventorySlot> SlotMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventorySlot* InventorySlot;


public:

	UUI(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float PercentHealth);

	UFUNCTION(BlueprintCallable)
	void SetTime(int _Hour, int _Minute);

	UFUNCTION(BlueprintCallable)
	void SetDate(int _Month, int _Date, int _Year);

	UFUNCTION(BlueprintCallable)
	void DisplayEquipSlots(class UInventoryComponent* _InventoryComponent);

	UFUNCTION(BlueprintCallable)
	void UpdateEquipSlots();

};
