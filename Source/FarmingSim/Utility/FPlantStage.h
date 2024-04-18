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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<FPlantStage> PlantStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DaysGrown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APlantBase> PlantClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
};