// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantableGround.h"
#include "../Characters/BasePlayer.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "../FarmingSim.h"

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
	PlantableLocations.SetNum(24);

	this->GetActorBounds(false, origin, boxExtent);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, boxExtent.ToString());

	double x = boxExtent.X / 6.0f;
	double y = boxExtent.Y / 4.0f;
	double startX = 0;
	double startY = 0;
	for (int i = 0; i < PlantableLocations.Num(); i++)
	{
		PlantableLocations[i] = FVector(startX, startY, 32.0f);
		startX += x;
		if (startX >= boxExtent.X)
		{
			startX = 0;
			startY += y;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor::Red, PlantableLocations[i].ToString());
	}
	
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

