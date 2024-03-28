// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() : HealthMax(5.0f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthCurrent = HealthMax;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DoDamage);
}


void UHealthComponent::DoDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	HealthCurrent = FMath::Clamp(HealthCurrent - GetDamage(DamageType, Damage), 0.0f, HealthMax);
	if (HealthCurrent > 0)
	{
		OnHealthChanged.Broadcast(HealthCurrent / HealthMax);
	}
	else
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::DoDamage);
		OnHealthChanged.Broadcast(HealthCurrent / HealthMax);

	}
}

float UHealthComponent::GetDamage(const UDamageType* DamageType, float Damage)
{
	return 1.0f;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FHealthDelegate* UHealthComponent::GetHealthDelegate()
{
	return &OnHealthChanged;
}

