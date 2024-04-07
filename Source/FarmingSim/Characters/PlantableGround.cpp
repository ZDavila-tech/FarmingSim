// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantableGround.h"
#include "../Characters/BasePlayer.h"
#include "Engine/StaticMesh.h"
#include "../Widgets/PlotWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../FarmingSim.h"

// Sets default values
APlantableGround::APlantableGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root"));
	SetRootComponent(DefaultRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	StaticMesh->SetWorldScale3D(FVector(0.39f, 0.39f, 0.01f));

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Plot Widget"));
	Widget->SetupAttachment(RootComponent);
	Widget->SetRelativeRotation(FRotator(90.0f, 90.0f, 0.0f));
	Widget->SetRelativeScale3D(FVector(0.198f, 0.198f, 0.198f));
	Widget->SetRelativeLocation(FVector(0.0f, 0.0f, 2.0f));

}

// Called when the game starts or when spawned
void APlantableGround::BeginPlay()
{
	Super::BeginPlay();

	Widget->SetVisibility(false);
}

// Called every frame
void APlantableGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlantableGround::LookAtPlot(ABasePlayer PlayerCharacter)
{
	Widget->SetVisibility(true);
}

void APlantableGround::PlantTrees(class ABasePlayer PlayerCharacter)
{
}

void APlantableGround::PlantSeeds(class ABasePlayer PlayerCharacter)
{
}

void APlantableGround::PlowSoil(class ABasePlayer PlayerCharacter)
{
}

void APlantableGround::WaterPlants(class ABasePlayer PlayerCharacter)
{
}

void APlantableGround::DestroyPlant(class ABasePlayer PlayerCharacter)
{
}

