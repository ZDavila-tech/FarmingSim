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
	if (TXT_Date)
	{
		UE_LOG(Game, Warning, TEXT("No Valid Text"));
	}
}

void UUI::NativeConstruct()
{
}

void UUI::SetHealth(float PercentHealth)
{
	BAR_Health->SetPercent(PercentHealth);
}

void UUI::SetTime(int _Hour, int _Minute)
{
	FString AmPmString;
	FString Time;
	if (_Hour >= 12.0f)
	{
		AmPmString = "PM";
		if (_Hour > 12.0f)
		{
			_Hour = _Hour - 12.0f;
		}
	}
	else
	{
		AmPmString = "AM";
		if (_Hour == 0.0f)
		{
			_Hour = 12.0f;
		}
		
	}

	if (_Minute < 10.0f)
	{
		FString min = FString::Printf(TEXT("0%d"), _Minute);
		Time = FString::Printf(TEXT("%d : %s %s"), _Hour, *min, *AmPmString);
	}
	else
	{
		Time = FString::Printf(TEXT("%d : %d %s"), _Hour, _Minute, *AmPmString);
	}
	TXT_Time->SetText(FText::FromString(Time));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Time);
}

void UUI::SetDate(int _Month, int _Date, int _Year)
{
	FString Date = FString::Printf(TEXT("Month %d Day %d Year %d"), _Month, _Date, _Year);
	TXT_Date->SetText(FText::FromString(Date));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Date);
}
