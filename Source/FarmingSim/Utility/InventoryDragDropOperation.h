// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class FARMINGSIM_API UInventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInventoryComponent* InventoryComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int ContentIndex;

public:
	void SetVariables(UInventoryComponent* _InventoryComp, int _ContentIndex);
	int GetContentIndex();
	UInventoryComponent* GetComp();
};
