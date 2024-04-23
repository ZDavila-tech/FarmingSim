// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenu.h"
#include "InventoryGrid.h"
#include "../Components/InventoryComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UInventoryMenu::NativeConstruct()
{
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	WBP_InventoryGrid->DisplayInventory(PC->GetPawn()->GetComponentByClass<UInventoryComponent>());
	FInputModeUIOnly WidgetMode;
	WidgetMode.SetWidgetToFocus(WBP_InventoryGrid->GetCachedWidget());
	PC->SetInputMode(WidgetMode);
	PC->SetPause(true);
	PC->bShowMouseCursor = true;
}

void UInventoryMenu::NativeDestruct()
{
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
		PC->SetPause(false);
	}
}

FReply UInventoryMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == InventoryButton)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Key Pressed");
		RemoveFromParent();
		return FReply::Handled();
	}
	else
	{
		return  FReply::Unhandled();
	}
}


