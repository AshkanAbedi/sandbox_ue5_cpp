// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InventorySystem/Public/InventoryWidget.h"

DEFINE_LOG_CATEGORY(LogBasePlayerController);

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogBasePlayerController, Warning, TEXT("BasePlayerController Initiated"));

	if (InventoryWidgetClass)
	{
		InventoryWidgetInstance = CreateWidget<UInventoryWidget>(this, InventoryWidgetClass);
		if (InventoryWidgetInstance)
		{
			InventoryWidgetInstance->AddToViewport();
			UE_LOG(LogTemp, Log, TEXT("InventorySlotWidget Added to the Screen"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Create InventorySlotWidget"));
		}
	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContext)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Added Mapping Context: %s"), *CurrentContext->GetName()));
		}
	}
}

void ABasePlayerController::RemoveUI()
{
	if (InventoryWidgetInstance)
	{
		InventoryWidgetInstance->RemoveFromParent();
		InventoryWidgetInstance = nullptr;
		UE_LOG(LogTemp, Log, TEXT("InventorySlotWidget Removed from the Screen"));
	}
}
