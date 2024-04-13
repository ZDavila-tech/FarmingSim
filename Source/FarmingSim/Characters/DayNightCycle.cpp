// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycle.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/VolumetricCloudComponent.h"

// Sets default values
ADayNightCycle::ADayNightCycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root"));
	SetRootComponent(DefaultRoot);

	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("Sky Light Component"));
	SkyLight->SetWorldLocation(FVector(0.0f, 0.0f, 150.0f));


	CompassMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Compass Mesh"));
	CompassMesh->SetUsingAbsoluteRotation(true);

	DirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Directional Light"));
	SM_SkySphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_SkySphere"));
	SM_SkySphere->SetupAttachment(DirectionalLight);
	ExpontentialHeightFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("Exponential Height Fog"));
	VolumetricCloud = CreateDefaultSubobject<UVolumetricCloudComponent>(TEXT("Volumetric Cloud"));
}

// Called when the game starts or when spawned
void ADayNightCycle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADayNightCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

