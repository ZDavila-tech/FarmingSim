// Fill out your copyright notice in the Description page of Project Settings.


#include "Store.h"
#include "Engine/StaticMesh.h"
#include "../BasePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "../../Widgets/InteractMenus/GeneralStoreMenu.h"

// Sets default values
AStore::AStore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AStore::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStore::HandleInteract(ABasePlayer* PlayerCharacter)
{
	Super::HandleInteract(PlayerCharacter);
	Menu->AddToViewport();
}

FText AStore::LookAt()
{
	return FText::FromString("Shop");
}

void AStore::WalkedAway()
{
}

