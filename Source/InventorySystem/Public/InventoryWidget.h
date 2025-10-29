// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotData.h"
#include "InventoryWidget.generated.h"

class UInventoryComponent;

UCLASS()
class INVENTORYSYSTEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	FSlotData SlotData;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FText GetQuantityText() const;

protected:
	virtual void NativeConstruct() override;
	
private:
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;
	
};
