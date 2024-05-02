// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "WorldCollision.h"
#include "../Interfaces/InteractInterface.h"
#include "EnhancedInputComponent.h"
#include "ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "../Widgets/ActionSlot.h"
#include "Engine/DataTable.h"
#include "../Utility/FItemStruct.h"
#include "../Utility/FSlotStruct.h"
#include "../FarmingSim.h"
#include "../Characters/BasePlayer.h"
#include "../Tools/BaseTool.h"
#include "../Characters/PlantableGround.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	InteractRange = 100.0f;
	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Content.SetNum(InventorySize);
	Player = Cast<ABasePlayer>(GetOwner());
	Update();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UInventoryComponent::PickUp(const FInputActionValue& Value)
{
	if (CanInteract)
	{
		if (LookAtActor)
		{
			UItemComponent* Comp = LookAtActor->GetComponentByClass<class UItemComponent>();
			if (IsValid(Comp))
			{
				Comp->HandleInteract(Cast<ABasePlayer>(GetOwner()));
				//return;
			}
		}
		Update();
		Player->GetEquipUpdate()->Broadcast(CurrentIndexEquipped);
	}
}


void UInventoryComponent::DropItem(FName ItemID, int Quantity)
{
}

void UInventoryComponent::Update()
{
	OnInventoryUpdate.Broadcast();
	for (int i = 0; i < Content.Num(); i++)
	{
		if (Content[i].ItemID == "")
		{
			Content[i].ItemID = "None";
			Content[i].Quantity = 0;
			Content[i].Equipped = false;
		}
	}

}

void UInventoryComponent::FindSlot(FName ItemID, int& Index, bool& isSlotFound)
{
	for (int i = 0; i < Content.Num(); i++)
	{
		if (Content[i].ItemID == ItemID)
		{
			if (Content[i].Quantity < GetLimit(ItemID))
			{
				Index = i;
				isSlotFound = true;
				return;
			}
			else
			{
				Index = 0;
				isSlotFound = false;
				return;
			}
		}
	}

	Index = -1;
	isSlotFound = false;
	return;
}

int UInventoryComponent::GetLimit(FName ItemID) const
{
	FItemStruct* OutRow = ItemDataTable->FindRow<FItemStruct>(ItemID, "");
	if (OutRow)
	{
		return OutRow->Limit;
	}
	else
	{
		return -1;
	}
}

void UInventoryComponent::AddToStack(int Index, int Quantity)
{
	FSlotStruct temp(Content[Index].ItemID, Content[Index].Quantity + Quantity, false);
	Content[Index] = temp;
}

bool UInventoryComponent::AnyEmptySlots(int& Index)
{
	for (int i = 0; i < Content.Num(); i++)
	{
		if (Content[i].Quantity == 0)
		{
			Index = i;
			return true;
		}

	}
	Index = -1;
	return false;
}

bool UInventoryComponent::CreateStack(FName ItemID, int Quantity)
{
	int Index;
	if (AnyEmptySlots(Index))
	{
		Content[Index] = FSlotStruct(ItemID, Quantity, false);
		return true;
	}

	return false;
}

FItemStruct UInventoryComponent::GetItemData(FName ItemID) const
{
	if (ItemID == "None")
	{
		return FItemStruct();
	}
	else
	{
		return FItemStruct(*ItemDataTable->FindRow<FItemStruct>(ItemID, ""));
	}
}

FVector UInventoryComponent::GetDropLocation() const
{
	FHitResult HitActor;
	float Radius = 100.0f;
	FVector Location = Cast<AActor>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetActorLocation();
	FVector Start = Location + (Cast<AActor>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetActorForwardVector() * 150.0f);
	FVector End = Start - FVector(0.0f, 0.0f, 500.0f) ;
	ECollisionChannel Channel = ECC_Visibility;
	FCollisionQueryParams Params;

	if (GetWorld()->LineTraceSingleByChannel(HitActor, Start, End, Channel, Params))
	{
		return HitActor.Location;
	}

	return FVector();
}

void UInventoryComponent::TransferSlots(int SourceIndex, UInventoryComponent* SourceInventory, int DestinationIndex)
{
	FSlotStruct LocalContent = SourceInventory->Content[SourceIndex];
	if (DestinationIndex >= 0)
	{
		if (LocalContent.ItemID == Content[DestinationIndex].ItemID)
		{
			FName tempName;
			int tempValue = FMath::Clamp(LocalContent.Quantity + Content[DestinationIndex].Quantity - GetLimit(LocalContent.ItemID), 0, GetLimit(LocalContent.ItemID));
			if (tempValue > 0)
			{
				tempName = LocalContent.ItemID;
			}
			else
			{
				tempName = "None";
			}
			SourceInventory->Content[SourceIndex].ItemID = tempName;
			SourceInventory->Content[SourceIndex].Quantity= tempValue;

			Content[DestinationIndex].ItemID = LocalContent.ItemID;
			Content[DestinationIndex].Quantity =
				FMath::Clamp(LocalContent.Quantity + Content[DestinationIndex].Quantity, 0, GetLimit(LocalContent.ItemID));
			Update();
			SourceInventory->Update();
		}
		else
		{
			SourceInventory->Content[SourceIndex] = Content[DestinationIndex];
			Content[DestinationIndex] = LocalContent;
			Update();
			SourceInventory->Update();
		}
	}

}

void UInventoryComponent::AddToInventory(FName ItemID, int Quantity, bool& Success, int& QuantityRemaining)
{
	int LocalQuantityRemaining = Quantity;
	bool LocalHasFailed = false;
	int LocalIndex;
	bool HasFoundSlot;
	while (LocalQuantityRemaining > 0 && !LocalHasFailed)
	{
		FindSlot(ItemID, LocalIndex, HasFoundSlot);
		if (HasFoundSlot)
		{
			AddToStack(LocalIndex, 1);
			--LocalQuantityRemaining;
			Update();
		}
		else
		{
			if (LocalIndex != -1)
			{
				LocalHasFailed = true;
			}
			else
			{
				int temp = 0;
				if (AnyEmptySlots(temp))
				{
					if (CreateStack(ItemID, 1))
					{
						--LocalQuantityRemaining;
						Update();
					}
					else
					{
						LocalHasFailed = true;
					}
				}
				else
				{
					LocalHasFailed = true;
				}
			}
		}
	}
	Success = !LocalHasFailed;
	QuantityRemaining = LocalQuantityRemaining;
	return;
}

void UInventoryComponent::RemoveFromInventory(int Index, bool RemoveAll, bool IsUsed)
{
	FName LocalItem = Content[Index].ItemID;
	int LocalQuantity = Content[Index].Quantity;

	if (RemoveAll || LocalQuantity == 1)
	{
		Content[Index].ItemID = "None";
		Content[Index].Quantity = 0;
		Content[Index].Equipped = false;
		if (IsUsed)
		{

		}
		else
		{
			DropItem(LocalItem, LocalQuantity);
		}
	}
	else
	{
		Content[Index].Quantity = LocalQuantity - 1;
		if (IsUsed)
		{

		}
		else
		{
			DropItem(LocalItem, 1);
		}
	}
	Update();
}

void UInventoryComponent::EquipWeapon(int Index)
{
	for (int i = 0; i < Content.Num(); i++)
	{
		UnequipWeapon(i);
	}
	Content[Index].Equipped = true;
	if (Content[Index].ItemID == "")
	{
		Player->WeaponChildActorComp->SetChildActorClass(NULL);
		Player->Widget->SetVisibility(false);
	}
	else
	{
		FItemStruct OutRow = GetItemData(Content[Index].ItemID);
		Player->WeaponChildActorComp->SetChildActorClass(OutRow.ItemClass);
		AItemBase* Item = Cast<AItemBase>(Player->WeaponChildActorComp->GetChildActor());
		Item->Equip();
		Player->Widget->SetVisibility(true);
		Player->ActionSlot->SetActionText(Item->Actions[0]);
		Player->ActionSlot->SetMouseImage(false);
	}
	Update();
}

void UInventoryComponent::UnequipWeapon(int Index)
{
	Content[Index].Equipped = false;
}

void UInventoryComponent::UseItem(const FInputActionValue& Value)
{
	FItemStruct OutRow = GetItemData(Content[CurrentIndexEquipped].ItemID);
	if (!OutRow.Name.IsEmpty())
	{
		TSubclassOf<ABaseTool> ToolClass = TSubclassOf<ABaseTool>(OutRow.ItemClass);
		if (ToolClass)
		{
			APlantableGround* Ground = Cast<APlantableGround>(LookAtActor);
			if (Ground)
			{
				Ground->HandleInteract(Player);
			}
			else
			{
				//Tool->Use();
			}
		}
		Update();
	}
	else
	{
		APlantableGround* Ground = Cast<APlantableGround>(LookAtActor);
		if (Ground)
		{
			Ground->HandleInteract(Player);
		}
		Update();
	}
}

void UInventoryComponent::SaveInventory()
{
}

FOnInventoryUpdate* UInventoryComponent::GetUpdateDelegate()
{
	return &OnInventoryUpdate;
}

