// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class FARMINGSIM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isToolEquipped;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentIndexEquipped;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int InteractRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AActor* LookAtActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int InventorySize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<struct FSlotStruct> Content;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* ItemDataTable;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Implementable events
	UFUNCTION(BlueprintImplementableEvent) 
	void DropItem(FName ItemID, int Quantity);

	UFUNCTION(BlueprintImplementableEvent)
	void MoveItem(int SourceIndex, UInventoryComponent* SourceInventory, int DestinationIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void Remove(int Index, bool RemoveAll, bool IsUsed);

	UFUNCTION(BlueprintImplementableEvent)
	void Update();

	UFUNCTION(BlueprintImplementableEvent)
	void UseItemEvent(int Index);

	UFUNCTION(BlueprintImplementableEvent)
	void Interact(AActor* TargetActor);

	UFUNCTION(BlueprintImplementableEvent)
	void EquipEvent(int Index);

	//Functions
	UFUNCTION(BlueprintCallable)
	void InteractionTrace();

	UFUNCTION(BlueprintCallable)
	void FindSlot(FName ItemID, int& Index, bool& isSlotFound);

	UFUNCTION(BlueprintCallable)
	int GetLimit(FName ItemID) const;

	UFUNCTION(BlueprintCallable)
	void AddToStack(int Index, int Quantity);

	UFUNCTION(BlueprintCallable)
	bool AnyEmptySlots(int& Index);

	UFUNCTION(BlueprintCallable)
	bool CreateStack(FName ItemID, int Quantity);

	UFUNCTION(BlueprintCallable)	//Needs to be edited when FSlotStruct created
	FItemStruct GetItemData(FName ItemID) const;

	UFUNCTION(BlueprintCallable)
	FVector GetDropLocation() const;

	UFUNCTION(BlueprintCallable)
	void TransferSlots(int SourceIndex, UInventoryComponent* SourceInventory, int DestinationIndex);

	UFUNCTION(BlueprintCallable)
	void AddToInventory(FName ItemID, int Quantity, bool& Success, int& QuantityRemaining);

	UFUNCTION(BlueprintCallable)
	void RemoveFromInventory(int Index, bool RemoveAll, bool IsUsed);

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(int Index);

	UFUNCTION(BlueprintCallable)
	void UnequipWeapon(int Index);

	UFUNCTION(BlueprintCallable)
	void UseItem(int Index);

	UFUNCTION(BlueprintCallable)
	void SaveInventory();
};
