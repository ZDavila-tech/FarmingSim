// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonCharacter.h"
#include "InputActionValue.h"
#include "../Utility/FPlayerInfo.h"
#include "BasePlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipUpdate, int, _EquipIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrencyUpdate, int, _Currency);

UCLASS(Blueprintable, BlueprintType)
class FARMINGSIM_API ABasePlayer : public ACommonCharacter
{
	GENERATED_BODY()
	
public:
	ABasePlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetComponent* Widget;
	class UActionSlot* ActionSlot;

	UPROPERTY(EditDefaultsOnly)
	class UInventoryComponent* InventoryComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerController* PlayerController;

protected:
	virtual void BeginPlay() override;
	
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxDetector;

	//Game Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UPlayerAnimInstance* PlayerAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AFarmingSimHUD* HUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UFarmingSimGameInstance* GameInstance;

	//Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enhanced Input")
	class UPlayerInputConfigData* InputActions;

	//Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UPauseMenu> PauseClass;

	class UPauseMenu* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UActionSlot> ActionSlotClass;

	

	class UUI* UIRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Currency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UInventoryMenu> InventoryClass;

	class UInventoryMenu* InventoryMenu;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnEquipUpdate OnEquipUpdate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
	FOnCurrencyUpdate OnCurrencyUpdate;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Handle Move Input
	void Move(const FInputActionValue& Value);

	//Handle look input
	void Look(const FInputActionValue& Value);

	//Handle jump input
	void Jump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);

	//Hande player pause input
	void OpenPause(const FInputActionValue& Value);

	//Handle Use Item input
	void Scroll(const FInputActionValue& Value);

	//Handle Inventory Input
	void OpenInventory(const FInputActionValue& Value);

	//Handle Switching slots in the inventory
	void EquipSlot1(const FInputActionValue& Value);
	void EquipSlot2(const FInputActionValue& Value);
	void EquipSlot3(const FInputActionValue& Value);
	void EquipSlot4(const FInputActionValue& Value);
	void EquipSlot5(const FInputActionValue& Value);
	void EquipSlot6(const FInputActionValue& Value);
	void EquipSlot7(const FInputActionValue& Value);
	void EquipSlot8(const FInputActionValue& Value);
	void EquipSlot9(const FInputActionValue& Value);
	void EquipSlot10(const FInputActionValue& Value);

	//Access Animations
	UPlayerAnimInstance* GetPlayerAnim();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	FOnEquipUpdate* GetEquipUpdate();

};
