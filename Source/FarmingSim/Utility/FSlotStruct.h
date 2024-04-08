#pragma once

#include "CoreMinimal.h"
#include "FSlotStruct.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FSlotStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName ItemID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Quantity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Equipped;
};