// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightCycle.generated.h"

UCLASS()
class FARMINGSIM_API ADayNightCycle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNightCycle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkyLightComponent* SkyLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* CompassMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDirectionalLightComponent* DirectionalLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SM_SkySphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkyAtmosphereComponent* SkyAtmosphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UExponentialHeightFogComponent* ExpontentialHeightFog;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UVolumetricCloudComponent* VolumetricCloud;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
