// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Interfaces/InteractInterface.h"
#include "InteractableActor.generated.h"

UCLASS()
class FARMINGSIM_API AInteractableActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABasePlayer* Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* DefaultRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUserWidget* Menu;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Interact Interface
	void HandleInteract(class ABasePlayer* PlayerCharacter) override;

	FText LookAt() override;

	void WalkedAway() override;
};
