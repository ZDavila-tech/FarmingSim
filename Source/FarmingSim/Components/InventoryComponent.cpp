// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "WorldCollision.h"
#include "../Interfaces/InteractInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "../Utility/FItemStruct.h"
#include "../Utility/FSlotStruct.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InteractionTrace();
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::InteractionTrace()
{
	FHitResult HitActor;
	float Radius = 100.0f;
	FVector Start = Cast<AActor>(UGameplayStatics::GetPlayerController(GetWorld(),0))->GetActorLocation();
	FVector End = Start + (Cast<AActor>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetActorForwardVector() * InteractRange);
	ECollisionChannel Channel = ECC_GameTraceChannel1;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	if (GetWorld()->SweepSingleByChannel(HitActor, Start, End, FQuat::Identity, Channel, FCollisionShape::MakeSphere(Radius), Params))
	{
		if (HitActor.GetActor() != LookAtActor)
		{
			LookAtActor = HitActor.GetActor();
		}
	}
}

void UInventoryComponent::FindSlot(FName ItemID, int& Index, bool& isSlotFound)
{
	for (int i = 0; Content.Num(); i++)
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
	return FItemStruct(*ItemDataTable->FindRow<FItemStruct>(ItemID, ""));
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
}

void UInventoryComponent::AddToInventory(FName ItemID, int Quantity, bool& Success, int& QuantityRemaining)
{
}

void UInventoryComponent::RemoveFromInventory(int Index, bool RemoveAll, bool IsUsed)
{
}

void UInventoryComponent::EquipWeapon(int Index)
{
}

void UInventoryComponent::UnequipWeapon(int Index)
{
}

void UInventoryComponent::UseItem(int Index)
{
}

void UInventoryComponent::SaveInventory()
{
}

