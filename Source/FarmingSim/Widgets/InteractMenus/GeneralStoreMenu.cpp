// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralStoreMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UGeneralStoreMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGeneralStoreMenu::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UGeneralStoreMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
