// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Onion.h"


AItem_Onion::AItem_Onion()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AItem_Onion::BeginPlay()
{
	Super::BeginPlay();
}

void AItem_Onion::HandleInteract(ABasePlayer* PlayerCharacter)
{
	Super::HandleInteract(PlayerCharacter);
}

FText AItem_Onion::LookAt()
{
	return Super::LookAt();
}
