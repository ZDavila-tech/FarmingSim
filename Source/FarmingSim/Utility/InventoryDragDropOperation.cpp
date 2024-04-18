// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDragDropOperation.h"

void UInventoryDragDropOperation::SetVariables(UInventoryComponent* _InventoryComp, int _ContentIndex)
{
	InventoryComp = _InventoryComp;
	ContentIndex = _ContentIndex;
}

int UInventoryDragDropOperation::GetContentIndex()
{
	return ContentIndex;
}

UInventoryComponent* UInventoryDragDropOperation::GetComp()
{
	return InventoryComp;
}
