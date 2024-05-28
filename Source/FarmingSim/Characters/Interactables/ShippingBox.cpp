// Fill out your copyright notice in the Description page of Project Settings.


#include "ShippingBox.h"
#include "Engine/StaticMesh.h"
#include "../../Components/InventoryComponent.h"
#include "../../Widgets/InteractMenus/ShippingMenu.h"
#include "../BasePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "../DayNightCycle.h"
#include "../../FarmingSim.h"

// Sets default values
AShippingBox::AShippingBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ShippingInventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
}

// Called when the game starts or when spawned
void AShippingBox::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DayNightClass, OutActor);
	DayNight = Cast<ADayNightCycle>(OutActor[0]);
	DayNight->GetDateDelegate()->AddDynamic(this, &AShippingBox::RemoveItems);
}

// Called every frame
void AShippingBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShippingBox::HandleInteract(ABasePlayer* PlayerCharacter)
{
	Super::HandleInteract(PlayerCharacter);
	Cast<UShippingMenu>(Menu)->ShippingInven = ShippingInventoryComp;
	ShippingInventoryComp->GetMoneyDelegate()->AddDynamic(Cast<UShippingMenu>(Menu), &UShippingMenu::SetMoneyEarned);
	Menu->AddToViewport();
}

FText AShippingBox::LookAt()
{
	return FText::FromString("Open");
}

void AShippingBox::WalkedAway()
{
}

void AShippingBox::RemoveItems(int Month, int Day, int Year)
{
	Player->SetMoney(ShippingInventoryComp->CalculateMoney());
	for (int i = 0; i < ShippingInventoryComp->Content.Num(); i++)
	{
		ShippingInventoryComp->RemoveFromInventory(i, true, false);
	}
}

