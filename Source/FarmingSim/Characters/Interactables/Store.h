// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Interfaces/InteractInterface.h"
#include "InteractableActor.h"
#include "Store.generated.h"

UCLASS()
class FARMINGSIM_API AStore : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Interact Interface
	void HandleInteract(class ABasePlayer* PlayerCharacter) override;

	FText LookAt() override;

	void WalkedAway() override;
};
