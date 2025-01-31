// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Utility/FPlantStage.h"
#include "PlantBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHarvested);

UCLASS()
class FARMINGSIM_API APlantBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> CropClass;

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
	int ToGrowing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* GrowingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ToHarvest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* HarvestableMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isHarvestable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPlantStruct PlantInfo;

	//To access day change
	class ADayNightCycle* DayNightCycle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADayNightCycle> DayNightClass;

	TArray<AActor*> OutActor;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnHarvested OnHarvested;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetPlantInfo(int _DaysGrown, FVector _Location);

	UFUNCTION()
	virtual void GrowPlant(int Month, int Day, int Year);

	virtual void SetStage(int _DaysGrown);

	FOnHarvested* GetHarvested();
};
