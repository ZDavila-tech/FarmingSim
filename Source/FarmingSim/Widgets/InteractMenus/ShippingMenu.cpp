// Fill out your copyright notice in the Description page of Project Settings.


#include "ShippingMenu.h"
#include "../InventoryGrid.h"
#include "../../Components/InventoryComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "../../Characters/Interactables/ShippingBox.h"
#include "Kismet/GameplayStatics.h"
#include "../../Characters/BasePlayer.h"
#include "../../FarmingSim.h"

void UShippingMenu::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(Game, Error, TEXT("Entered Shipping Menu"));
	UInventoryComponent* InvnComp = PC->GetPawn()->GetComponentByClass<UInventoryComponent>();
	WBP_PlayerGrid->DisplayInventory(InvnComp);

	WBP_ShippingGrid->DisplayInventory(ShippingInven);
	ShippingInven->GetMoneyDelegate()->Broadcast(ShippingInven->CalculateMoney());
}

void UShippingMenu::NativeDestruct()
{
	Super::NativeDestruct();

}

FReply UShippingMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UShippingMenu::SetMoneyEarned(int _TotalMoney)
{
	Money = _TotalMoney;
	TXT_TotalEarned->SetText(FText::FromString(FString::FromInt(_TotalMoney)));
}

