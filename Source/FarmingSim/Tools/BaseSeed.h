// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTool.h"
#include "BaseSeed.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API ABaseSeed : public ABaseTool
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APlantBase> PlantClass;
protected:
	

public:
	void Use();
	
	UFUNCTION(BlueprintCallable)
	TSubclassOf<class APlantBase> GetPlant() const;
};
