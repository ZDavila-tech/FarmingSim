// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UActionSlot::SetActionText(FText _Action)
{
	TXT_Action->SetText(_Action);
}

void UActionSlot::SetMouseImage(bool _isRightClick)
{
	if (_isRightClick)
	{
		IMG_Mouse->SetBrushFromTexture(MouseImages[0]);
	}
	else
	{
		IMG_Mouse->SetBrushFromTexture(MouseImages[1]);
	}
}
