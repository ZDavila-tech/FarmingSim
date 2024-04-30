// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "../Utility/FItemStruct.h"
#include "../Utility/InventoryDragDropOperation.h"
#include "../Components/InventoryComponent.h"
#include "DragMenu.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"



void UInventorySlot::NativeConstruct()
{
	FItemStruct* OutRow = ItemDataTable->FindRow<FItemStruct>(ItemID, "");
	if (OutRow)
	{
		IMG_Item->SetBrushFromTexture(OutRow->Icon);
		TXT_Quantity->SetText(FText::FromString(FString::Printf(TEXT("%d"), Quantity)));
		IMG_Item->SetVisibility(ESlateVisibility::Visible);
		TXT_Quantity->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		IMG_Item->SetVisibility(ESlateVisibility::Hidden);
		TXT_Quantity->SetVisibility(ESlateVisibility::Hidden);
	}
}

FReply UInventorySlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (ItemID != " ")
	{
		if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			FEventReply OutEvent = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
			return OutEvent.NativeReply;
		}
		else
		{
			if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
			{
				//Action Menu Actions
				return FReply::Handled();
			}
			else
			{
				return FReply::Unhandled();
			}
		}
	}
	else
	{
		return FReply::Unhandled();
	}
	
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	DragMenu = CreateWidget<UDragMenu>(UGameplayStatics::GetPlayerController(GetWorld(), 0), DragMenuClass);
	UInventoryDragDropOperation* DDSlot = NewObject<UInventoryDragDropOperation>();
	DDSlot->DefaultDragVisual = DragMenu;
	DDSlot->SetVariables(InventoryComponent, ContentIndex);
	OutOperation = DDSlot;
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UInventoryDragDropOperation* DDSlot = Cast<UInventoryDragDropOperation>(InOperation);
	if (DDSlot) 
	{
		if (DDSlot->GetContentIndex() != ContentIndex || DDSlot->GetComp() != InventoryComponent)
		{
			InventoryComponent->TransferSlots(DDSlot->GetContentIndex(), DDSlot->GetComp(), ContentIndex);
			return true;
		}
	}
	else
	{
		return false;
	}
	return false;
}

void UInventorySlot::HighlightSlot()
{
	FItemStruct* OutRow = ItemDataTable->FindRow<FItemStruct>(ItemID, "");
	if (InventoryComponent->CurrentIndexEquipped == ContentIndex)
	{
		BTN_SlotButton->BackgroundColor = FLinearColor(FColor::Red);
	}
	else
	{
		BTN_SlotButton->BackgroundColor = FLinearColor(FColor::Black);
	}
}
