// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTool.h"
#include "Kismet/GameplayStatics.h"
#include "../Characters/BasePlayer.h"
#include "../Animations/PlayerAnimInstance.h"

// Sets default values
ABaseTool::ABaseTool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABaseTool::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	//NOTE:: Want to move this into Item when Inventory is connected to implementation
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

}

// Called every frame
void ABaseTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseTool::Use()
{
	Super::Use();
	UGameplayStatics::ApplyDamage(Player, BaseDamage, GetInstigatorController(), this, DamageTypeClass);
}

