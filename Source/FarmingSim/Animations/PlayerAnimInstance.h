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
	//Farming Animations. Public so other scripts can choose which action they want to do.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Sequences")
	UAnimSequence* PlantingAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Sequences")
	UAnimSequence* PlowingAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Sequences")
	UAnimSequence* ChoppingAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Sequences")
	UAnimSequence* SmashingAnimation;
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCharacterMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bool Variables")
	bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bool Variables")
	bool ShouldMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bool Variables")
	bool isTired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bool Variables")
	bool isFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bool Variables")
	bool isBusy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float Variables")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Float Variables")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle Timer;

	

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	//Farming Actions
	void SetBusy(float _AnimationTime);
	void SetNotBusy();
	void HandleFarmActions(UAnimSequence* _Animation);
};
