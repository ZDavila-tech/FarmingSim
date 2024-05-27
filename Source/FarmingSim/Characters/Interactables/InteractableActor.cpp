// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include "Engine/StaticMesh.h"
#include "../BasePlayer.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root"));
	SetRootComponent(DefaultRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::HandleInteract(ABasePlayer* PlayerCharacter)
{
	Menu = CreateWidget<UUserWidget>(PlayerCharacter->PlayerController, MenuClass);
}

FText AInteractableActor::LookAt()
{
	return FText();
}

void AInteractableActor::WalkedAway()
{
}

