// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGrid.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UInventoryGrid : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UWrapBox* BOX_InventoryGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventorySlot* InventorySlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UInventorySlot> SlotMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* InventoryComponent;

public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void DisplayInventory(class UInventoryComponent* _InventoryComponent);
	UFUNCTION()
	void UpdateInventory();
};
