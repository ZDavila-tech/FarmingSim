// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ACharacter>(GetOwningActor());
	PlayerController = GetWorld()->GetFirstPlayerController();
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
		Direction = CalculateDirection(Velocity, GetOwningActor()->GetActorRotation());
		ShouldMove = (Speed > 3.0 && MovementComp->GetCurrentAcceleration() != FVector(0.0f, 0.0f, 0.0f));
		isFalling = MovementComp->IsFalling();
	}

}

void UPlayerAnimInstance::SetBusy(float _AnimationTime)
{
	isBusy = true;
	GetOwningActor()->DisableInput(PlayerController);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UPlayerAnimInstance::SetNotBusy, _AnimationTime, false);
}

void UPlayerAnimInstance::SetNotBusy()
{
	GetOwningActor()->EnableInput(PlayerController);
	isBusy = false;
}

void UPlayerAnimInstance::HandleFarmActions(UAnimSequence* _Animation)
{
	PlaySlotAnimationAsDynamicMontage(_Animation, "Action");
	SetBusy(_Animation->GetPlayLength());
}


