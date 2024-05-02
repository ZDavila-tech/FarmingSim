// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "../Components/InventoryComponent.h"
#include "../Components/ItemComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "../Widgets/ActionSlot.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "../Animations/PlayerAnimInstance.h"
#include "../Utility/FarmingSimHUD.h"
#include "../Components/HealthComponent.h"
#include "../Utility/PlayerInputConfigData.h"
#include "../Interfaces/InteractInterface.h"
#include "../Interfaces/FarmingInterface.h"
#include "../Widgets/PauseMenu.h"
#include "../Widgets/InventoryMenu.h"
#include "../Widgets/UI.h"
#include "../Utility/FSlotStruct.h"
#include "../FarmingSimGameInstance.h"
#include "../FarmingSim.h"


ABasePlayer::ABasePlayer()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->AddLocalOffset(FVector(0.0f, 0.0f, 90.0f));
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Comp"));

	BoxDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxDetector->SetupAttachment(RootComponent);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Action Widget"));
	Widget->SetupAttachment(RootComponent);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Widget->SetDrawSize(FVector2D(200, 20));
	Widget->SetWorldLocation(FVector(0.0f, 0.0f, 130.0f));
	Widget->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();


	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController == nullptr)
	{
		UE_LOG(Game, Error, TEXT("No controller"));
		Destroy();
		return;
	}

	HUD = Cast<AFarmingSimHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	GameInstance = Cast<UFarmingSimGameInstance>(GetWorld()->GetGameInstance());

	UIRef = HUD->GetUI();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMapping, 0);
	}
	
	PlayerAnimation = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	ActionSlot = CreateWidget<UActionSlot>(PlayerController, ActionSlotClass);
	Widget->SetWidget(ActionSlot);

	HealthComponent->GetHealthDelegate()->AddDynamic(UIRef, &UUI::SetHealth);
	BoxDetector->OnComponentBeginOverlap.AddDynamic(this, &ABasePlayer::OnBeginOverlap);
	BoxDetector->OnComponentEndOverlap.AddDynamic(this, &ABasePlayer::OnEndOverlap);
	OnEquipUpdate.AddDynamic(InventoryComp, &UInventoryComponent::EquipWeapon);
	OnCurrencyUpdate.AddDynamic(UIRef, &UUI::SetMoney);
	InventoryComp->InventorySize = 16;
	InventoryComp->Content.Insert(FSlotStruct("BasePlow", 1, false),0);
	InventoryComp->Content.Insert(FSlotStruct("BaseHammer", 1, false), 1);
	InventoryComp->Content.Insert(FSlotStruct("OnionSeed", 1, false), 2);
	UIRef->DisplayEquipSlots(InventoryComp);
	OnCurrencyUpdate.Broadcast(Currency);
	OnEquipUpdate.Broadcast(0);

}

void ABasePlayer::Tick(float DeltaTime)
{
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind Actions
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &ABasePlayer::Look);
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &ABasePlayer::Move);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Started, this, &ABasePlayer::Jump);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Completed, this, &ABasePlayer::StopJump);
	PEI->BindAction(InputActions->InputPauseMenu, ETriggerEvent::Completed, this, &ABasePlayer::OpenPause);
	PEI->BindAction(InputActions->InputUseItem, ETriggerEvent::Completed, InventoryComp, &UInventoryComponent::UseItem);
	PEI->BindAction(InputActions->InputInteract, ETriggerEvent::Completed, InventoryComp, &UInventoryComponent::PickUp);
	PEI->BindAction(InputActions->InputInventory, ETriggerEvent::Completed, this, &ABasePlayer::OpenInventory);
	PEI->BindAction(InputActions->InputScrollWheel, ETriggerEvent::Triggered, this, &ABasePlayer::Scroll);
	PEI->BindAction(InputActions->InputEquip1, ETriggerEvent::Completed, this, &ABasePlayer::EquipSlot1);
	PEI->BindAction(InputActions->InputEquip2, ETriggerEvent::Completed, this, &ABasePlayer::EquipSlot2);
	PEI->BindAction(InputActions->InputEquip3, ETriggerEvent::Completed, this, &ABasePlayer::EquipSlot3);
	PEI->BindAction(InputActions->InputEquip4, ETriggerEvent::Completed, this, &ABasePlayer::EquipSlot4);
	PEI->BindAction(InputActions->InputEquip5, ETriggerEvent::Completed, this, &ABasePlayer::EquipSlot5);
	PEI->BindAction(InputActions->InputEquip6, ETriggerEvent::Completed, this, &ABasePlayer::EquipSlot6);
	PEI->BindAction(InputActions->InputEquip7, ETriggerEvent::Completed, this, &ABasePlayer::EquipSlot7);
	PEI->BindAction(InputActions->InputEquip8, ETriggerEvent::Completed, this, &ABasePlayer::EquipSlot8);
	PEI->BindAction(InputActions->InputEquip9, ETriggerEvent::Completed, this, &ABasePlayer::EquipSlot9);
	PEI->BindAction(InputActions->InputEquip10, ETriggerEvent::Completed, this, &ABasePlayer::EquipSlot10);
}

void ABasePlayer::Move(const FInputActionValue& Value)
{
	if (PlayerController != nullptr)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, PlayerController->GetControlRotation().Yaw, 0);

		if (MoveValue.Y != 0.0f)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, MoveValue.Y);
		}
		if (MoveValue.X != 0.0f)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void ABasePlayer::Look(const FInputActionValue& Value)
{
	if (PlayerController != nullptr)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();

		if (LookValue.X != 0.0f)
		{
			AddControllerYawInput(LookValue.X);
		}
		if (LookValue.Y != 0.0f)
		{
			AddControllerPitchInput(LookValue.Y);
		}
	}
}

void ABasePlayer::Jump(const FInputActionValue& Value)
{
	Super::Jump();
}

void ABasePlayer::StopJump(const FInputActionValue& Value)
{
	Super::StopJumping();
}

void ABasePlayer::OpenPause(const FInputActionValue& Value)
{
	PauseMenu = CreateWidget<UPauseMenu>(PlayerController, PauseClass);
	if (PauseMenu == nullptr)
	{
		UE_LOG(Game, Error, TEXT("Need a Pause Menu"));
		return;
	}
	PauseMenu->AddToViewport();
}

void ABasePlayer::Scroll(const FInputActionValue& Value)
{
	
	float index = Value.GetMagnitude();
	if (index > 0)
	{
		InventoryComp->CurrentIndexEquipped++;
		if (InventoryComp->CurrentIndexEquipped > 9)
		{
			InventoryComp->CurrentIndexEquipped = 0;
		}
		OnEquipUpdate.Broadcast(InventoryComp->CurrentIndexEquipped);
	}
	else
	{
		InventoryComp->CurrentIndexEquipped--;
		if (InventoryComp->CurrentIndexEquipped < 0)
		{
			InventoryComp->CurrentIndexEquipped = 9;
		}
		OnEquipUpdate.Broadcast(InventoryComp->CurrentIndexEquipped);
	}
}

void ABasePlayer::OpenInventory(const FInputActionValue& Value)
{
	InventoryMenu = CreateWidget<UInventoryMenu>(PlayerController, InventoryClass);
	if (InventoryMenu == nullptr)
	{
		UE_LOG(Game, Error, TEXT("Need a Inventory Menu"));
		return;
	}
	InventoryMenu->AddToViewport();
}

void ABasePlayer::EquipSlot1(const FInputActionValue& Value)
{
	InventoryComp->CurrentIndexEquipped = 0;
	OnEquipUpdate.Broadcast(0);
}

void ABasePlayer::EquipSlot2(const FInputActionValue& Value)
{
	InventoryComp->CurrentIndexEquipped = 1;
	OnEquipUpdate.Broadcast(1);
}

void ABasePlayer::EquipSlot3(const FInputActionValue& Value)
{
	InventoryComp->CurrentIndexEquipped = 2;
	OnEquipUpdate.Broadcast(2);
}

void ABasePlayer::EquipSlot4(const FInputActionValue& Value)
{
	InventoryComp->CurrentIndexEquipped = 3;
	OnEquipUpdate.Broadcast(3);
}

void ABasePlayer::EquipSlot5(const FInputActionValue& Value)
{
	InventoryComp->CurrentIndexEquipped = 4;
	OnEquipUpdate.Broadcast(4);
}

void ABasePlayer::EquipSlot6(const FInputActionValue& Value)
{
	InventoryComp->CurrentIndexEquipped = 5;
	OnEquipUpdate.Broadcast(5);
}

void ABasePlayer::EquipSlot7(const FInputActionValue& Value)
{
	InventoryComp->CurrentIndexEquipped = 6;
	OnEquipUpdate.Broadcast(6);
}

void ABasePlayer::EquipSlot8(const FInputActionValue& Value)
{
	InventoryComp->CurrentIndexEquipped = 7;
	OnEquipUpdate.Broadcast(7);
}

void ABasePlayer::EquipSlot9(const FInputActionValue& Value)
{
	InventoryComp->CurrentIndexEquipped = 8;
	OnEquipUpdate.Broadcast(8);
}

void ABasePlayer::EquipSlot10(const FInputActionValue& Value)
{
	InventoryComp->CurrentIndexEquipped = 9;
	OnEquipUpdate.Broadcast(9);
}

UPlayerAnimInstance* ABasePlayer::GetPlayerAnim()
{
	return PlayerAnimation;
}

void ABasePlayer::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		Cast<IInteractInterface>(OtherActor)->LookAt();
		InventoryComp->CanInteract = true;
		InventoryComp->LookAtActor = OtherActor;
	}
	else if (OtherActor->GetComponentByClass<UItemComponent>())
	{
		Cast<IInteractInterface>(OtherActor->GetComponentByClass<UItemComponent>())->LookAt();
		Widget->SetVisibility(true);
		ActionSlot->SetActionText(FText::FromString(("Pick Up")));
		InventoryComp->CanInteract = true;
		InventoryComp->LookAtActor = OtherActor;
	}
	else if (OtherActor->GetClass()->ImplementsInterface(UFarmingInterface::StaticClass()))
	{
		Cast<IFarmingInterface>(OtherActor)->LookAtPlot(this);
		InventoryComp->CanInteract = true;
		InventoryComp->LookAtActor = OtherActor;
	}
}

void ABasePlayer::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		Cast<IInteractInterface>(OtherActor)->WalkedAway();
		InventoryComp->CanInteract = false;
		InventoryComp->LookAtActor = nullptr;
	}
	else if (OtherActor->GetComponentByClass<UItemComponent>())
	{
		Cast<IInteractInterface>(OtherActor->GetComponentByClass<UItemComponent>())->WalkedAway();
		Widget->SetVisibility(false);
		InventoryComp->CanInteract = false;
		InventoryComp->LookAtActor = nullptr;
	}

}

FOnEquipUpdate* ABasePlayer::GetEquipUpdate()
{
	return &OnEquipUpdate;
}


