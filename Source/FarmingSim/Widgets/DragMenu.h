// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragMenu.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UDragMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	class UImage* IMG_Icon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName ItemID;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* ItemDataTable;

public:
	virtual void NativeConstruct() override;
	
};
