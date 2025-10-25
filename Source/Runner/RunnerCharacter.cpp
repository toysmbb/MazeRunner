// Copyright Epic Games, Inc. All Rights Reserved.

#include "RunnerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Runner.h"

ARunnerCharacter::ARunnerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(HealthBarWidgetClass) 
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), HealthBarWidgetClass);
		if(Widget) 
		{
			Widget->AddToViewport();
			HealthBarWidget = Cast<UUMG_Hud>(Widget);
		}
	}
	
	if(InteractWidgetClass)
	{
		InteractWidget = CreateWidget<UUserWidget>(GetWorld(), InteractWidgetClass);
		InteractWidget->AddToViewport(0);
		InteractWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	CurrentHealth = 1;
	MaxHealth = 3;
}

void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CanInteract();
}

void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ARunnerCharacter::Interact);
	}
	else
	{
		UE_LOG(LogRunner, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ARunnerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ARunnerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ARunnerCharacter::Die()
{
	GetMesh()->SetSimulatePhysics(true);
	DisableInput(nullptr);
}

void ARunnerCharacter::ModifyHealth(int32 Delta)
{
	if (CurrentHealth <= 0) return;
	int32 OldHealth = CurrentHealth;

	CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0, MaxHealth);

	if(HealthBarWidget) 
	{
		HealthBarWidget->UpdateHealthBar(GetPercentHealth());
	}

	if (CurrentHealth <= 0) 
	{
		Die();
	}
}

void ARunnerCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ARunnerCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ARunnerCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ARunnerCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void ARunnerCharacter::CanInteract()
{
	Cast<APlayerController>(GetController())->GetPlayerViewPoint(ViewVector, ViewRotation);
	FVector VecDirection = ViewRotation.Vector() * 700.0f;
	FVector InteractEnd = ViewVector + VecDirection;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(InteractionHitResult, ViewVector, InteractEnd, ECollisionChannel::ECC_GameTraceChannel1, QueryParams);
	if (Cast<ASwitcher>(InteractionHitResult.GetActor()))
	{
		InteractWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else 
	{
		InteractWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}


void ARunnerCharacter::Interact()
{
	ASwitcher* Switcher = Cast<ASwitcher>(InteractionHitResult.GetActor());
	if(Switcher)
	{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
	Switcher->bisLightCanState();
    }
}
