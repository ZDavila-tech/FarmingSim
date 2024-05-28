// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStoreSlot.h"
#include "Components/TextBlock.h"
#include "../../Utility/FItemStruct.h"
#include "Engine/DataTable.h"

void UBaseStoreSlot::NativeConstruct()
{
	TXT_ItemName->SetText(Name);
	TXT_Price->SetText(FText::FromString(FString::Printf(TEXT("%f"), price)));
	
}
