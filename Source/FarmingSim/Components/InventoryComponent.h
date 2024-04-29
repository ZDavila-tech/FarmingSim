// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CanInteract;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AActor* LookAtActor;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int InteractRange;

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* ItemDataTable;

	class IInteractInterface* InteractInterface;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnInventoryUpdate OnInventoryUpdate;

public:	

	UPROPERTY(EditDefaultsOnly)
	int InventorySize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<struct FSlotStruct> Content;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Handle Interact for PickUp Input
	void PickUp(const FInputActionValue& Value);

	void UseItem(const FInputActionValue& Value);
	
	//Implementable events
	UFUNCTION(BlueprintCallable)
	void DropItem(FName ItemID, int Quantity);

	UFUNCTION(BlueprintCallable)
	void Update();

	UFUNCTION(BlueprintCallable)
	void EquipEvent(int Index);

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

	UFUNCTION(BlueprintCallable)
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
	void SaveInventory();

	FOnInventoryUpdate* GetUpdateDelegate();
};
