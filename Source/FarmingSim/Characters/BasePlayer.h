// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonCharacter.h"
#include "InputActionValue.h"
#include "../Interfaces/InteractInterface.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FARMINGSIM_API ABasePlayer : public ACommonCharacter, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	ABasePlayer();

protected:
	virtual void BeginPlay() override;
	
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly)
	class UInventoryComponent* InventoryComp;

	//Game Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APlayerController* PlayerController;

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

	class UUI* UIRef;

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
	void UseItem(const FInputActionValue& Value);

	
	void HandleInteract(class ABasePlayer* PlayerCharacter);
	
	FText LookAt();
};
