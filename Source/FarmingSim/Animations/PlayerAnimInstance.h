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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCharacterMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isTired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;


public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
};
