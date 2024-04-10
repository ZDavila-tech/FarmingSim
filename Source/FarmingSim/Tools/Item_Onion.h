// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Item_Onion.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API AItem_Onion : public AItemBase
{
	GENERATED_BODY()
public:
	AItem_Onion();

protected:
	virtual void BeginPlay() override;

};
