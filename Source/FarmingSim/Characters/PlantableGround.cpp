// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantableGround.h"
#include "../Characters/BasePlayer.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlantableGround::APlantableGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APlantableGround::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlantableGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlantableGround::PlantTrees(class ABasePlayer PlayerCharacter)
{
}

void APlantableGround::PlantSeeds(class ABasePlayer PlayerCharacter)
{
}

void APlantableGround::PlowSoil(class ABasePlayer PlayerCharacter)
{
}

void APlantableGround::WaterPlants(class ABasePlayer PlayerCharacter)
{
}

void APlantableGround::DestroyPlant(class ABasePlayer PlayerCharacter)
{
}

