// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBasePlayerController, Log, All);

class UInputMappingContext;
class UInventorySlotWidget;

UCLASS(Abstract)
class PLAYERCHARACTER_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UInventorySlotWidget> InventorySlotClass;

	UPROPERTY()
	UInventorySlotWidget* InventorySlotWidget;

	void RemoveUI();

protected:
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContext;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override; 
	
};
