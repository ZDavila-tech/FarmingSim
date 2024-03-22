// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "../Utility/PlayerInputConfigData.h"
#include "../FarmingSim.h"


ABasePlayer::ABasePlayer()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->AddLocalOffset(FVector(0.0f, 0.0f, 90.0f));
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController == nullptr)
	{
		UE_LOG(Game, Error, TEXT("No controller"));
		Destroy();
		return;
	}
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMapping, 0);;
	}
	

}

void ABasePlayer::Tick(float DeltaTime)
{
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind Actions
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &ABasePlayer::Look);
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &ABasePlayer::Move);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Started, this, &ABasePlayer::Jump);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Completed, this, &ABasePlayer::StopJump);
}

void ABasePlayer::Move(const FInputActionValue& Value)
{
	if (PlayerController != nullptr)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, PlayerController->GetControlRotation().Yaw, 0);

		if (MoveValue.Y != 0.0f)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, MoveValue.Y);
		}
		if (MoveValue.X != 0.0f)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void ABasePlayer::Look(const FInputActionValue& Value)
{
	if (PlayerController != nullptr)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();

		if (LookValue.X != 0.0f)
		{
			AddControllerYawInput(LookValue.X);
		}
		if (LookValue.Y != 0.0f)
		{
			AddControllerPitchInput(LookValue.Y);
		}
	}
}

void ABasePlayer::Jump(const FInputActionValue& Value)
{
	Super::Jump();
}

void ABasePlayer::StopJump(const FInputActionValue& Value)
{
	Super::StopJumping();
}


