// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
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
	

}

void ABasePlayer::Tick(float DeltaTime)
{
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}
