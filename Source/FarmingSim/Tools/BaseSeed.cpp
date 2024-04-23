// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSeed.h"
#include "../Plants/PlantBase.h"

void ABaseSeed::Use()
{

}

TSubclassOf<class APlantBase> ABaseSeed::GetPlant() const
{
	return PlantClass;
}
