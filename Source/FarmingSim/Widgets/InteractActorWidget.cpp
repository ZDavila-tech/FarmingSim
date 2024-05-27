// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractActorWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../Characters/BasePlayer.h"

void UInteractActorWidget::NativeConstruct()
{
	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Player = Cast<ABasePlayer>(PC->GetPawn());
	FInputModeUIOnly WidgetMode;
	PC->SetInputMode(WidgetMode);
	PC->SetPause(true);
	PC->bShowMouseCursor = true;
}

void UInteractActorWidget::NativeDestruct()
{
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
		PC->SetPause(false);
	}
}

FReply UInteractActorWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == ExitButton)
	{
		RemoveFromParent();
		return FReply::Handled();
	}
	else
	{
		return  FReply::Unhandled();
	}
}
