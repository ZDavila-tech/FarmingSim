// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "PlayerInputConfigData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FARMINGSIM_API UPlayerInputConfigData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputPauseMenu;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputUseItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputScrollWheel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEquip1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEquip2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEquip3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEquip4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEquip5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEquip6;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEquip7;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEquip8;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEquip9;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEquip10;
};
