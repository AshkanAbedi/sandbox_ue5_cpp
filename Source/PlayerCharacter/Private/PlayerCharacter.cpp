// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogPlayerCharacter);

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetHiddenInGame(false);

	GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetWorldLocation(FVector(0.f, 0.f, -90.f));
	
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 100.0f, 0.0f);
	
	GetCharacterMovement()->MaxWalkSpeed = 180.f;
	GetCharacterMovement()->MaxAcceleration = 400.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 30.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 300.f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetWorldLocation(FVector(0, 40, 70));
	CameraBoom->TargetArmLength = 130.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BaseCamera"));
	BaseCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	BaseCamera->bUsePawnControlRotation = false;

	AimCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("AimCamera"));
	AimCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	AimCamera->bUsePawnControlRotation = false;
	AimCamera->SetRelativeLocation(FVector(50, 0, 0));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerMovementState = EMovementStates::Ems_Idle;
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
			EnhancedInputComponent->BindAction(AimInput, ETriggerEvent::Started, this, &APlayerCharacter::Aim);
			EnhancedInputComponent->BindAction(MoveInput, ETriggerEvent::Completed, this, &APlayerCharacter::StopMove);
		}
	}
	else
	{
		UE_LOG(LogPlayerCharacter, Error, TEXT("Failed to find an Enhanced Input component"));
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	if (GetController() != nullptr)
	{
		PlayerMovementState = EMovementStates::Ems_Walking;
		const FVector Forward = GetActorForwardVector();
		const FVector Right = GetActorRightVector();
		AddMovementInput(Forward, MoveVector.Y);
		AddMovementInput(Right, MoveVector.X);
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Move X: %f Y: %f"), MoveVector.X, MoveVector.Y));
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D LookVector = Value.Get<FVector2D>();
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y * -1.f);
	}
}

void APlayerCharacter::Aim()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Aim"));
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	BaseCamera->SetActive(false);
	AimCamera->SetActive(true);
}

void APlayerCharacter::StopMove()
{
	PlayerMovementState = EMovementStates::Ems_Idle;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Stop Move"));
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if WITH_EDITOR

	const FVector Start = GetActorLocation();
	const FVector End = GetActorForwardVector() * 100.f;
	constexpr float ArrowSize = 15.f;
	const FColor ArrowColor = FColor::Green;
	DrawDebugDirectionalArrow(GetWorld(), Start, Start + End, ArrowSize, ArrowColor, false, -1.f, 0, 5.f);
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Yellow, FString::Printf(TEXT("Current Speed: %f"), GetVelocity().Size()));
	
#endif
	
}



