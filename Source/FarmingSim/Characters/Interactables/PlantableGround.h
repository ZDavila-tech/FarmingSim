// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Interfaces/FarmingInterface.h"
#include "InteractableActor.h"
#include "PlantableGround.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickedUp);
UCLASS()
class FARMINGSIM_API APlantableGround : public AInteractableActor, public IFarmingInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantableGround();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollider;

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
	bool NeedsEmptying;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTransform PlotLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<class APlantBase> PlantType;

	class APlantBase* CurrentPlant;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Interact Interface
	void HandleInteract(class ABasePlayer* PlayerCharacter) override;

	FText LookAt() override;

	void WalkedAway() override;

	//Farming Interface
	void LookAtPlot(class ABasePlayer* PlayerCharacter) override;
	//Plant trees in area
	void PlantTrees(UChildActorComponent* _Tool) override;
	//Plant plants in area
	void PlantSeeds(UChildActorComponent* _Tool) override;
	//Plow soil before planting
	void PlowSoil(UChildActorComponent* _Tool) override;
	//Water plants
	void WaterPlants(UChildActorComponent* To_Toolol) override;
	//Remove plants from plowed area
	void DestroyPlant(UChildActorComponent* _Tool) override;

	UFUNCTION()
	void ClearPlot();

};
