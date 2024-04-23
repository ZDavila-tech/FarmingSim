// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/FarmingInterface.h"
#include "../Interfaces/InteractInterface.h"
#include "PlantableGround.generated.h"

UCLASS()
class FARMINGSIM_API APlantableGround : public AActor, public IFarmingInterface, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantableGround();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterial* GrassMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterial* DirtMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isPlowed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isWatered;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isEmpty;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTransform PlotLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Interact Interface
	void HandleInteract(class ABasePlayer* PlayerCharacter) override;

	FText LookAt() override;

	void WalkedAway() override;

	//Farming Interface
	void LookAtPlot(class ABasePlayer PlayerCharacter) override;
	//Plant trees in area
	void PlantTrees(class ABasePlayer PlayerCharacter) override;
	//Plant plants in area
	void PlantSeeds(class ABaseSeed* _Seed) override;
	//Plow soil before planting
	void PlowSoil(class ABasePlayer PlayerCharacter) override;
	//Water plants
	void WaterPlants(class ABasePlayer PlayerCharacter) override;
	//Remove plants from plowed area
	void DestroyPlant(class ABasePlayer PlayerCharacter) override;

};
