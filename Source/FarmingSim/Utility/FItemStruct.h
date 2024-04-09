#pragma once

#include "CoreMinimal.h"
#include "FItemStruct.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	 
public:
	UPROPERTY(EditDefaultsOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> ItemClass;

	UPROPERTY(EditDefaultsOnly)
	int Limit;

	UPROPERTY(EditDefaultsOnly)
	float BuyCost;

	UPROPERTY(EditDefaultsOnly)
	float SellCost;
};