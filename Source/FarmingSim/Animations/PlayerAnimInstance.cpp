// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ACharacter>(GetOwningActor());
	if (Character != nullptr)
	{
		MovementComp = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	if (Character != nullptr)
	{
		Velocity = MovementComp->Velocity;
		Speed = Velocity.Size2D();
		ShouldMove = (Speed > 3.0 && MovementComp->GetCurrentAcceleration() != FVector(0.0f, 0.0f, 0.0f));
		isFalling = MovementComp->IsFalling();
	}

}


