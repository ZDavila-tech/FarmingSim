// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralStoreMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../StoreWidgets/BaseStoreSlot.h"
#include "../../Utility/FItemStruct.h"
#include "Engine/DataTable.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "../../Characters/BasePlayer.h"

void UGeneralStoreMenu::NativeConstruct()
{
	Super::NativeConstruct();
	for (auto row : ItemDataTable->GetRowMap())
	{
		FItemStruct* data = (FItemStruct*)(row.Value);
		if (data->BuyCost > 0.0f)
		{
			StoreSlot = CreateWidget<UBaseStoreSlot>(PC, SlotMenu);
			StoreSlot->Name = data->Name;
			StoreSlot->price = data->BuyCost;
			BOX_Collection->AddChildToVerticalBox(StoreSlot);
		}
	}
	SetMoney();
}

void UGeneralStoreMenu::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UGeneralStoreMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UGeneralStoreMenu::SetMoney()
{
	TXT_Money->SetText(FText::FromString(FString::Printf(TEXT("%d"), Player->GetMoney())));
}
