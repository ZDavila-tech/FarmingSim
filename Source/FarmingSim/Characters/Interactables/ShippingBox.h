// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Interfaces/InteractInterface.h"
#include "InteractableActor.h"
#include "ShippingBox.generated.h"

UCLASS()
class FARMINGSIM_API AShippingBox : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShippingBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* ShippingInventoryComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ADayNightCycle* DayNight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADayNightCycle> DayNightClass;

	TArray<AActor*> OutActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Interact Interface
	void HandleInteract(class ABasePlayer* PlayerCharacter) override;

	FText LookAt() override;

	void WalkedAway() override;

	UFUNCTION()
	void RemoveItems(int Month, int Day, int Year);
};
