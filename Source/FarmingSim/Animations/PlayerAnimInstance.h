// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FARMINGSIM_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isDead;

public:
	
};
