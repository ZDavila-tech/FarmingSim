// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightCycle.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnTimelineEvent);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTimelineFloat, float, Output);

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
	class UDirectionalLightComponent* Moon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SM_SkySphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UExponentialHeightFogComponent* ExpontentialHeightFog;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UVolumetricCloudComponent* VolumetricCloud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCurveFloat* LightCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTimelineComponent* LightTimeLine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Location")
	float Latitude;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Location")
	float Longitude;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Location")
	float TimeZone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Location")
	float NorthOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Location")
	float Elevation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Location")
	float CorrectedElevation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Location")
	float Azimuth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Date")
	int Year;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Date")
	int Month;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Date")
	int Day;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Time")
	float ClockTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeToSet;

	FOnTimelineFloat UpdateFunction;
	FOnTimelineEvent TimelineFinished;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlayTimeline();

	void SetTime(float Time);

	void AddTime(float TimeToAdd);

	void UpdateSun();

	void UpdateDate();

	int GetDateFormat(float SolarTime, int& Hour, int& Minute);

	UFUNCTION()
	void TimelineFloatReturned(float value);

	UFUNCTION()
	void OnTimelineFinished();
};
