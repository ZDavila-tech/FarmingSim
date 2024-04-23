// Fill out your copyright notice in the Description page of Project Settings.


#include "DragMenu.h"
#include "../Utility/FItemStruct.h"
#include "Engine/DataTable.h"
#include "Components/Image.h"

void UDragMenu::NativeConstruct()
{
	FItemStruct* OutRow = ItemDataTable->FindRow<FItemStruct>(ItemID, "");

	if (OutRow)
	{
		IMG_Icon->SetBrushFromTexture(OutRow->Icon);
	}
}
