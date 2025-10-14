// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

DEFINE_LOG_CATEGORY(LogBasePlayerController);

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogBasePlayerController, Warning, TEXT("BasePlayerController Initiated"));
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContext)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
