#pragma once

#include "CoreMinimal.h"
#include "FItemStruct.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FItemStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	 
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<class AActor> ItemClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Limit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float BuyCost;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SellCost;
};