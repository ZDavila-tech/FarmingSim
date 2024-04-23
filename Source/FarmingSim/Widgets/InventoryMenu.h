// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenu.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	class UInventoryGrid* WBP_InventoryGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey InventoryButton;

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
