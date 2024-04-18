// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantBase.generated.h"

UCLASS()
class FARMINGSIM_API APlantBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* DefaultRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* SeedlingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* GrowingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* HarvestableMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isHarvestable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int DaysGrown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> CropClass;

	//To access day change
	class ADayNightCycle* DayNightCycle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADayNightCycle> DayNightClass;

	TArray<AActor*> OutActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void GrowPlant(int Month, int Day, int Year);

};
