// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTool.h"
#include "BasePlow.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API ABasePlow : public ABaseTool
{
	GENERATED_BODY()

public:
protected:
public:
	virtual void BeginPlay() override;
	void Use();
};
