// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FarmingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFarmingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FARMINGSIM_API IFarmingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void LookAtPlot(class ABasePlayer PlayerCharacter) = 0;
	//Plant trees in area
	virtual void PlantTrees(class ABasePlayer PlayerCharacter) = 0;
	//Plant plants in area
	virtual void PlantSeeds(class ABasePlayer PlayerCharacter) = 0;
	//Plow soil before planting
	virtual void PlowSoil(class ABasePlayer PlayerCharacter) = 0;
	//Water plants
	virtual void WaterPlants(class ABasePlayer PlayerCharacter) = 0;
	//Remove plants from plowed area
	virtual void DestroyPlant(class ABasePlayer PlayerCharacter) = 0;
};
