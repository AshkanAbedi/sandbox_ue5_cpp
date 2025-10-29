// Fill out your copyright notice in the Description page of Project Settings.
#include "InventoryWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FText UInventoryWidget::GetQuantityText() const
{
	return FText::AsNumber(SlotData.Quantity);
}

