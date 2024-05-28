// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractActorWidget.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UInteractActorWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerController* PC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABasePlayer* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FKey ExitButton;
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
