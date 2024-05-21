// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/InteractInterface.h"
#include "ShippingBox.generated.h"

UCLASS()
class FARMINGSIM_API AShippingBox : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShippingBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* DefaultRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* ShippingInventoryComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UShippingMenu> ShippingMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UShippingMenu* ShippingMenu;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Interact Interface
	void HandleInteract(class ABasePlayer* PlayerCharacter) override;

	FText LookAt() override;

	void WalkedAway() override;
};
