// Fill out your copyright notice in the Description page of Project Settings.
#include "InventorySlotWidget.h"
#include "SInventorySlot.h"

void UInventorySlotWidget::SetSlotData(const FSlotData& InSlotData)
{
	SlotData = InSlotData;
	if (MySlateWidget.IsValid())
	{
		MySlateWidget->Construct(SInventorySlot::FArguments(), SlotData);
	}
}

TSharedRef<SWidget> UInventorySlotWidget::RebuildWidget()
{
	MySlateWidget = SNew(SInventorySlot, SlotData);
	return MySlateWidget.ToSharedRef();
}


