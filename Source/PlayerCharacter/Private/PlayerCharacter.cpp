// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY(LogPlayerCharacter);

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetHiddenInGame(false);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BaseCamera"));
	BaseCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	BaseCamera->bUsePawnControlRotation = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveInput && LookInput)
		{
			EnhancedInputComponent->BindAction(MoveInput, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
			EnhancedInputComponent->BindAction(LookInput, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		}
	}
	else
	{
		UE_LOG(LogPlayerCharacter, Error, TEXT("Failed to find an Enhanced Input component"));
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (GetController() != nullptr)
	{
		const double MovementRightValue = Value.Get<FVector2D>().X;
		const double MovementForwardValue = Value.Get<FVector2D>().Y;
		
		const FVector RightVector = GetActorRightVector();
		const FVector ForwardVector = GetActorForwardVector();
		
		AddMovementInput(RightVector, MovementRightValue);
		AddMovementInput(ForwardVector, MovementForwardValue);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}



