// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/FarmingInterface.h"
#include "PlantableGround.generated.h"

UCLASS()
class FARMINGSIM_API APlantableGround : public AActor, public IFarmingInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantableGround();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsPlowed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsEmpty;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsWatered;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Plant trees in area
	void PlantTrees(class ABasePlayer PlayerCharacter) override;
	//Plant plants in area
	void PlantSeeds(class ABasePlayer PlayerCharacter) override;
	//Plow soil before planting
	void PlowSoil(class ABasePlayer PlayerCharacter) override;
	//Water plants
	void WaterPlants(class ABasePlayer PlayerCharacter) override;
	//Remove plants from plowed area
	void DestroyPlant(class ABasePlayer PlayerCharacter) override;

};
