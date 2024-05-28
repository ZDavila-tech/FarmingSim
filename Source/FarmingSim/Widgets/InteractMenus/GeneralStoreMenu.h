// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractActorWidget.h"
#include "GeneralStoreMenu.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UGeneralStoreMenu : public UInteractActorWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* BOX_Collection;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TXT_Money;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBaseStoreSlot* StoreSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UBaseStoreSlot> SlotMenu;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* ItemDataTable;

public:
	 void NativeConstruct() override;
	 void NativeDestruct() override;
	 FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	 void SetMoney();
};
