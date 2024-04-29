// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "../Components/InventoryComponent.h"
#include "../Components/ItemComponent.h"
#include "Components/BoxComponent.h"
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

	HealthComponent->GetHealthDelegate()->AddDynamic(UIRef, &UUI::SetHealth);
	BoxDetector->OnComponentBeginOverlap.AddDynamic(this, &ABasePlayer::OnBeginOverlap);
	BoxDetector->OnComponentEndOverlap.AddDynamic(this, &ABasePlayer::OnEndOverlap);
	InventoryComp->Content.Insert(FSlotStruct("BasePlow", 1, false),0);

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
		InventoryComp->CanInteract = false;
		InventoryComp->LookAtActor = nullptr;
	}

}




