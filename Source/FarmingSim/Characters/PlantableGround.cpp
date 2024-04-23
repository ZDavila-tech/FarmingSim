// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantableGround.h"
#include "../Characters/BasePlayer.h"
#include "Engine/StaticMesh.h"
#include "../Widgets/PlotWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/Material.h"
#include "../Tools/BaseSeed.h"
#include "../Plants/PlantBase.h"
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

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(StaticMesh);
	BoxCollider->SetWorldLocation(FVector(0.0f, 0.0f, 1200.0f));
	BoxCollider->SetWorldScale3D(FVector(2.0f, 2.0f, 50.0f));

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

	StaticMesh->SetMaterial(0, GrassMaterial);
	PlotLocation = GetActorTransform();
	isEmpty = true;

}

// Called every frame
void APlantableGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlantableGround::HandleInteract(ABasePlayer* PlayerCharacter)
{
	UChildActorComponent* Tool = PlayerCharacter->GetComponentByClass<UChildActorComponent>();
	if (Tool)
	{
		ABaseSeed* seed = Cast<ABaseSeed>(Tool->GetChildActor());
		if (seed && isEmpty)
		{
			PlantSeeds(seed);
		}
		
	}
}

FText APlantableGround::LookAt()
{
	Widget->SetVisibility(true);
	return FText();
}

void APlantableGround::WalkedAway()
{
	Widget->SetVisibility(false);
}

void APlantableGround::LookAtPlot(ABasePlayer PlayerCharacter)
{
	Widget->SetVisibility(true);
}

void APlantableGround::PlantTrees(class ABasePlayer PlayerCharacter)
{
}

void APlantableGround::PlantSeeds(class ABaseSeed* _Seed)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<APlantBase>(_Seed->PlantClass, PlotLocation, SpawnInfo);
	isEmpty = false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Planted");
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

