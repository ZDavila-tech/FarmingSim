// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGrid.h"
#include "../Components/InventoryComponent.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "InventorySlot.h"
#include "../Utility/FSlotStruct.h"
#include "../Characters/BasePlayer.h"



void UInventoryGrid::NativeConstruct()
{
	if (InventoryComponent)
	{
		for (int i = 0; i < InventoryComponent->Content.Num(); i++)
		{
			InventorySlot = CreateWidget<UInventorySlot>(UGameplayStatics::GetPlayerController(GetWorld(), 0), SlotMenu);
			InventorySlot->ContentIndex = i;
			InventorySlot->ItemID = InventoryComponent->Content[i].ItemID;
			InventorySlot->Quantity = InventoryComponent->Content[i].Quantity;
			InventorySlot->InventoryComponent = InventoryComponent;
			BOX_InventoryGrid->AddChildToWrapBox(InventorySlot);
			//If equipped
		}
		InventoryComponent->GetUpdateDelegate()->AddDynamic(this, &UInventoryGrid::UpdateInventory);
	}
}

void UInventoryGrid::DisplayInventory(UInventoryComponent* _InventoryComponent)
{
	InventoryComponent = _InventoryComponent;
	if (InventoryComponent)
	{
		for(int i = 0; i<InventoryComponent->Content.Num();i++)
		{
			InventorySlot = CreateWidget<UInventorySlot>(UGameplayStatics::GetPlayerController(GetWorld(), 0), SlotMenu);
			InventorySlot->ContentIndex = i;
			InventorySlot->ItemID = InventoryComponent->Content[i].ItemID;
			InventorySlot->Quantity = InventoryComponent->Content[i].Quantity;
			InventorySlot->InventoryComponent = InventoryComponent;
			BOX_InventoryGrid->AddChildToWrapBox(InventorySlot);
			//If equipped
		}
		InventoryComponent->GetUpdateDelegate()->AddDynamic(this, &UInventoryGrid::UpdateInventory);
	}
}

void UInventoryGrid::UpdateInventory()
{
	BOX_InventoryGrid->ClearChildren();
	if (InventoryComponent)
	{
		for (int i = 0; i < InventoryComponent->Content.Num(); i++)
		{
			InventorySlot = CreateWidget<UInventorySlot>(UGameplayStatics::GetPlayerController(GetWorld(), 0), SlotMenu);
			InventorySlot->ContentIndex = i;
			InventorySlot->ItemID = InventoryComponent->Content[i].ItemID;
			InventorySlot->Quantity = InventoryComponent->Content[i].Quantity;
			InventorySlot->InventoryComponent = InventoryComponent;
			BOX_InventoryGrid->AddChildToWrapBox(InventorySlot);
			//If equipped
		}
		InventoryComponent->GetUpdateDelegate()->AddDynamic(this, &UInventoryGrid::UpdateInventory);
	}
}
