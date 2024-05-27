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

public:
	 void NativeConstruct() override;
	 void NativeDestruct() override;
	 FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
