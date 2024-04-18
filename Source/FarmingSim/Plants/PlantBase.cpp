// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantBase.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "../Characters/DayNightCycle.h"
#include "Kismet/GameplayStatics.h"
#include "../FarmingSim.h"

// Sets default values
APlantBase::APlantBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root"));
	SetRootComponent(DefaultRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	StaticMesh->SetMobility(EComponentMobility::Stationary);
}

// Called when the game starts or when spawned
void APlantBase::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->SetStaticMesh(SeedlingMesh);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DayNightClass, OutActor);
	Cast<ADayNightCycle>(OutActor[0])->GetDateDelegate()->AddDynamic(this, &APlantBase::GrowPlant);
}

// Called every frame
void APlantBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlantBase::GrowPlant(int Month, int Day, int Year)
{
	DaysGrown++;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%d"), DaysGrown));
}

