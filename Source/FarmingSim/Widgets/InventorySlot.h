// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* IMG_Item;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TXT_Quantity;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BTN_SlotButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDragMenu> DragMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* InventoryComponent;

	class UDragMenu* DragMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName ItemID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Quantity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ContentIndex;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* ItemDataTable;

	//Need Action Menu variable


protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
