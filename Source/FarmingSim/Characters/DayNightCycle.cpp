// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycle.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/VolumetricCloudComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SunPosition.h"


// Sets default values
ADayNightCycle::ADayNightCycle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root"));
	SetRootComponent(DefaultRoot);

	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("Sky Light Component"));
	SkyLight->SetWorldLocation(FVector(0.0f, 0.0f, 150.0f));
	SkyLight->SetupAttachment(RootComponent);

	Atmosphere = CreateDefaultSubobject<USkyAtmosphereComponent>(TEXT("Sky Atmosphere"));
	Atmosphere->SetupAttachment(RootComponent);

	CompassMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Compass Mesh"));
	CompassMesh->SetUsingAbsoluteRotation(true);
	CompassMesh->SetupAttachment(RootComponent);

	DirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Directional Light"));
	DirectionalLight->SetupAttachment(RootComponent);
	DirectionalLight->SetWorldLocation(FVector(0.0f, 0.0f, 100.0f));
	DirectionalLight->Intensity = 2.75f;
	DirectionalLight->LightSourceAngle = 0.5f;
	DirectionalLight->IndirectLightingIntensity = 2.0f;

	Moon = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Moon"));
	Moon->SetupAttachment(DirectionalLight);
	Moon->SetWorldRotation(FRotator(180.0f, 0.0f, 0.0f));
	Moon->Intensity = 0.26f;
	Moon->LightSourceAngle = 0.0f;
	Moon->bUseTemperature = true;
	Moon->Temperature = 12000.0f;
	Moon->ForwardShadingPriority = 1;
	Moon->AtmosphereSunLightIndex = 1;

	ExpontentialHeightFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("Exponential Height Fog"));
	ExpontentialHeightFog->SetupAttachment(RootComponent);
	VolumetricCloud = CreateDefaultSubobject<UVolumetricCloudComponent>(TEXT("Volumetric Cloud"));
	VolumetricCloud->SetupAttachment(RootComponent);


	LightTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	UpdateFunction.BindDynamic(this, &ADayNightCycle::TimelineUpdate);
	DayBegan.BindDynamic(this, &ADayNightCycle::TimelineBegin);
	TimelineFinished.BindDynamic(this, &ADayNightCycle::OnTimelineFinished);
	DayEnded.BindDynamic(this, &ADayNightCycle::OnTimelineFinished);
	MinChanged.BindDynamic(this, &ADayNightCycle::MinuteChanged);
}

// Called when the game starts or when spawned
void ADayNightCycle::BeginPlay()
{
	Super::BeginPlay();
	LightTimeLine->SetLooping(true);
	LightTimeLine->AddInterpFloat(LightCurve, UpdateFunction);
	LightTimeLine->SetTimelineFinishedFunc(TimelineFinished);
	LightTimeLine->AddEvent(24.0, DayEnded);
	LightTimeLine->AddEvent(0.0, DayBegan);

	for (int j = 0; j < 24.0; j++)
	{
		for (float i = 0.0f; i < 1.0f; i += (1.0 / 60.0f))
		{
			LightTimeLine->AddEvent(j+i, MinChanged);
		}
	}
	
	LightTimeLine->SetPlayRate((1.0f / (RealTimeDayNight * 60.0f)) * 24.0f);
	LightTimeLine->Play();
}

// Called every frame
void ADayNightCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ADayNightCycle::SetTime(float Time)
{
	TimeToSet = Time;
	LightTimeLine->SetNewTime(TimeToSet);
}

void ADayNightCycle::AddTime(float TimeToAdd)
{
	TimeToSet = (TimeToAdd + ClockTime) * 150.0f;

	if (TimeToAdd + ClockTime >= 24.0f)
	{
		TimeToSet = (TimeToSet - 24.0f) * 150.0f;
		UpdateDate();
		LightTimeLine->SetNewTime(TimeToSet);
	}
	else
	{
		LightTimeLine->SetNewTime(TimeToSet);
	}
}

void ADayNightCycle::UpdateSun()
{
	FSunPositionData SunData;
	if(DirectionalLight)
	{
		USunPositionFunctionLibrary::GetSunPosition(Latitude, Longitude, TimeZone, false, Year, Month, Day,
			FTimespan::FromHours(ClockTime).GetHours(), FTimespan::FromHours(ClockTime).GetMinutes(), FTimespan::FromHours(ClockTime).GetSeconds(), SunData);

		Elevation = SunData.Elevation;
		CorrectedElevation = SunData.CorrectedElevation;
		Azimuth = SunData.Azimuth;

		DirectionalLight->SetWorldRotation(FRotator(CorrectedElevation, Azimuth, 0.0f));
	}

	if (CompassMesh)
	{
		CompassMesh->SetWorldRotation(FRotator(0.0f, NorthOffset + 90.0f, 0.0f));
	}
}

void ADayNightCycle::UpdateDate()
{
	if (Day + 1 > FDateTime::DaysInMonth(Year, Month))
	{
		Day = 1;
		if (Month + 1 > 12)
		{
			Month = 1;
			Year++;
		}
		else
		{
			Month++;
		}
	}
	else
	{
		Day++;
	}	
}

int ADayNightCycle::GetDateFormat(float SolarTime, int& Hour, int& Minute)
{
	int Time = int(truncf(SolarTime) / 24.0f);

	Hour = int(trunc((SolarTime - Time) * 60.0f) / 60.0f);
	Minute = int(trunc((SolarTime - Hour) * 3600 + 0.5)/60.0f);

	return 1;
}

void ADayNightCycle::TimelineBegin()
{
	OnDayBegins.Broadcast(Month, Day, Year);
}

void ADayNightCycle::TimelineUpdate(float value)
{
	ClockTime = value;
	
	switch (DirectionalLight->Mobility)
	{
	case EComponentMobility::Movable:
		UpdateSun();
		break;
	case EComponentMobility::Static:
		break;
	case EComponentMobility::Stationary:
		break;
	}
}

void ADayNightCycle::OnTimelineFinished()
{
	UpdateDate();
	OnDayChanged.Broadcast(Month, Day, Year);
}

void ADayNightCycle::MinuteChanged()
{
	int Hour, Minute;
	GetDateFormat(ClockTime, Hour, Minute);
	OnMinuteChanged.Broadcast(Hour, Minute);
}

FDateDelegate* ADayNightCycle::GetDateDelegate()
{
	return &OnDayChanged;
}

FDateDelegate* ADayNightCycle::GetMorningDelegate()
{
	return &OnDayBegins;
}

FTimeDelegate* ADayNightCycle::GetTimeDelegate()
{
	return &OnMinuteChanged;
}

