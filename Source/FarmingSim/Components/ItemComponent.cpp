// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemComponent.h"
#include "../Characters/BasePlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InventoryComponent.h"
#include "../FarmingSim.h"

// Sets default values for this component's properties
UItemComponent::UItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UItemComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->SetReplicates(true);
	
}


// Called every frame
void UItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItemComponent::HandleInteract(ABasePlayer* PlayerCharacter)
{
	UInventoryComponent* tempInventory = PlayerCharacter->GetComponentByClass<class UInventoryComponent>();
	if (tempInventory)
	{
		//Add Dispatcher
		bool Success = false;
		int QuantityRemaining = 0;
		tempInventory->AddToInventory(ItemID.RowName, Quantity, Success, QuantityRemaining);
		if (Success)
		{	
			GetOwner()->Destroy();
		}
	}
}

FText UItemComponent::LookAt()
{
	return FText();
}

void UItemComponent::WalkedAway()
{

}

