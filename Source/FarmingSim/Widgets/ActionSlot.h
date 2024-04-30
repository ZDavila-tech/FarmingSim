// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionSlot.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UActionSlot : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TXT_Action;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UImage* IMG_Mouse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> MouseImages;

public:

	void SetActionText(FText _Action);

	void SetMouseImage(bool _isRightClick);
};
