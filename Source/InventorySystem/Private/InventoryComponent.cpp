// Fill out your copyright notice in the Description page of Project Settings.
#include "InventoryComponent.h"
#include "BaseItemData.h"
#include "SlotData.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializeGrid();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::InitializeGrid()
{
	InventoryGrid.SetNum(GetCapacity());
	for (FSlotData& Slot : InventoryGrid)
	{
		Slot.ItemData = nullptr;
		Slot.Quantity = 0;
	}
}

int32 UInventoryComponent::FindFirstEmptySlot() const
{
	for (int Index = 0; Index < InventoryGrid.Num(); Index++)
	{
		const FSlotData& Slot = InventoryGrid[Index];
		if (Slot.ItemData == nullptr || Slot.Quantity <= 0)
		{
			return Index;
		}
	}

	return INDEX_NONE;
}

int32 UInventoryComponent::CountEmptySlots() const
{
	int Count = 0;
	for (const FSlotData& Slot : InventoryGrid)
	{
		if (Slot.ItemData != nullptr)
		{
			Count++;
		}
	}
	return Count;
}

bool UInventoryComponent::TryAddItem(UBaseItemData* ItemData, int32 Quantity)
{
	if (!ItemData || Quantity <= 0)
	{
		return false;
	}

	int32 Remaining = Quantity;

	if (!ItemData->bIsStackable)
	{
		const int32 FreeSlots = CountEmptySlots();
		if (FreeSlots < Remaining)
		{
			
		}
	}
}

