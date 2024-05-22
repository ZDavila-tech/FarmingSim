// Fill out your copyright notice in the Description page of Project Settings.


#include "ShippingMenu.h"
#include "InventoryGrid.h"
#include "../Components/InventoryComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "../Characters/ShippingBox.h"
#include "Kismet/GameplayStatics.h"
#include "../Characters/BasePlayer.h"
#include "../FarmingSim.h"

void UShippingMenu::NativeConstruct()
{
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Player = Cast<ABasePlayer>(PC->GetPawn());
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
	if (InKeyEvent.GetKey() == ExitButton)
	{
		Player->SetMoney(Money);
		RemoveItems();
		RemoveFromParent();
		return FReply::Handled();
	}
	else
	{
		return  FReply::Unhandled();
	}
}

void UShippingMenu::SetMoneyEarned(int _TotalMoney)
{
	Money = _TotalMoney;
	TXT_TotalEarned->SetText(FText::FromString(FString::FromInt(_TotalMoney)));
}

void UShippingMenu::RemoveItems()
{
	for (int i = 0; i < ShippingInven->Content.Num(); i++)
	{
		ShippingInven->RemoveFromInventory(i, true, false);
	}
}
