// Fill out your copyright notice in the Description page of Project Settings.


#include "UI.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "../FarmingSim.h"

UUI::UUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (BAR_Health == nullptr)
	{
		UE_LOG(Game, Warning, TEXT("No Valid Bar"));
	}
}

void UUI::NativeConstruct()
{
}

void UUI::SetHealth(float PercentHealth)
{
	BAR_Health->SetPercent(PercentHealth);
}

void UUI::SetTime(int _Month, int _Date, int _Year)
{
	FText Date;
	Date.AsDate(FDateTime(_Year, _Month, _Date));
	
	TXT_Date->SetText(Date);
}

void UUI::SetData()
{
}
