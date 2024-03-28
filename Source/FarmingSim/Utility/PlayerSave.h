#pragma once

#include "CoreMinimal.h"
#include "PlayerSave.generated.h"

USTRUCT(BlueprintType)
struct FPlayerSave
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FName PlayerName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float Health;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FTransform PlayerTransform;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FRotator ControlRotation;

};