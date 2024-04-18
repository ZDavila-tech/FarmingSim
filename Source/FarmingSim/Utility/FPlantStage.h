#pragma once

#include "CoreMinimal.h"
#include "FPlantStage.generated.h"

UENUM(Blueprintable, BlueprintType)
enum FPlantStage
{
	SEEDLING UMETA(DisplayName = "Seedling"),
	GROWING UMETA(DisplayName = "Plant Growing"),
	HARVESTABLE UMETA(DisplayName = "Harvestable")
	
};

USTRUCT(Blueprintable, BlueprintType)
struct FPlantStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<FPlantStage> PlantStage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int DaysGrown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<class APlantBase> PlantClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Location;
};