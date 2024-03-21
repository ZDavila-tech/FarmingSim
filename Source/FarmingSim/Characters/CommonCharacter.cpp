// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonCharacter.h"
#include "../Components/HealthComponent.h"

// Sets default values
ACommonCharacter::ACommonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
}

// Called when the game starts or when spawned
void ACommonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACommonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACommonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

