#pragma once

#include "CoreMinimal.h"
#include "FSlotStruct.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FSlotStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Equipped;
};