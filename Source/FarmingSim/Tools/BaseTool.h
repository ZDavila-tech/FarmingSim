// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "BaseTool.generated.h"

UCLASS()
class FARMINGSIM_API ABaseTool : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ABasePlayer* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDamageType> DamageTypeClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Use();

};
