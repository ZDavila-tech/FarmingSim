// Fill out your copyright notice in the Description page of Project Settings.


#include "ShippingMenu.h"
#include "InventoryGrid.h"
#include "../Components/InventoryComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "../Characters/ShippingBox.h"
#include "Kismet/GameplayStatics.h"
#include "../FarmingSim.h"

void UShippingMenu::NativeConstruct()
{
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UE_LOG(Game, Error, TEXT("Entered Shipping Menu"));
	UInventoryComponent* InvnComp = PC->GetPawn()->GetComponentByClass<UInventoryComponent>();
	WBP_PlayerGrid->DisplayInventory(InvnComp);

	WBP_ShippingGrid->DisplayInventory(ShippingInven);

	FInputModeUIOnly WidgetMode;
	PC->SetInputMode(WidgetMode);
	PC->SetPause(true);
	PC->bShowMouseCursor = true;
}

void UShippingMenu::NativeDestruct()
{
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
		PC->SetPause(false);
	}
}

FReply UShippingMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return FReply::Handled();
}

void UShippingMenu::SetMoneyEarned(int _TotalMoney)
{
}
