// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDelegate, float, ratio);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class FARMINGSIM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HealthCurrent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HealthMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float NewDamage;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Health|Delagates")
	FHealthDelegate OnHealthChanged;

	UFUNCTION(BlueprintCallable)
	void DoDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
	UFUNCTION(BlueprintCallable)
	float GetDamage(const UDamageType* DamageType, float Damage);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FHealthDelegate* GetHealthDelegate();
		
};
