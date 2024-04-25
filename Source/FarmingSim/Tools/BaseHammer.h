// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTool.h"
#include "BaseHammer.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API ABaseHammer : public ABaseTool
{
	GENERATED_BODY()
public:
protected:
public:
	virtual void BeginPlay() override;
	void Use();
	
};
