// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSeed.h"
#include "../Plants/PlantBase.h"
#include "../Characters/BasePlayer.h"
#include "../Animations/PlayerAnimInstance.h"


void ABaseSeed::BeginPlay()
{
	Super::BeginPlay();
}

//For upgrading purposes
void ABaseSeed::Use()
{
	Player->GetPlayerAnim()->HandleFarmActions(Player->GetPlayerAnim()->PlantingAnimation);
}

void ABaseSeed::PlantSeed(TSubclassOf<class APlantBase> _PlantClass, FTransform _Location)
{
	Use();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<APlantBase>(_PlantClass, _Location, SpawnInfo);

}

TSubclassOf<class APlantBase> ABaseSeed::GetPlant() const
{
	return PlantClass;
}
