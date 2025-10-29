// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotData.h"
#include "InventorySlotWidget.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FSlotData SlotData;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetSlotData(const FSlotData& InSlotData);

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	TSharedPtr<class SInventorySlot> MySlateWidget;
	
};
