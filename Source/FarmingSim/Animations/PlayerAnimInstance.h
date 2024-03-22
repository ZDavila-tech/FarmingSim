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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool ShouldMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector Velocity;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
};
