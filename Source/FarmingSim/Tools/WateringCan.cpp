// Fill out your copyright notice in the Description page of Project Settings.


#include "WateringCan.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AWateringCan::AWateringCan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
}

// Called when the game starts or when spawned
void AWateringCan::BeginPlay()
{
	Super::BeginPlay();
	SetActorEnableCollision(false);
}

// Called every frame
void AWateringCan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

