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


void UInventoryComponent::TryStackItem(UBaseItemData* ItemData, int32 Quantity)
{
	int32 RemainingQuantity = Quantity;
	for (FSlotData& Slot : InventoryGrid)
	{
		if (Slot.ItemData == ItemData && Slot.Quantity < ItemData->MaxStackSize)
		{
			const int32 SpaceLeft = ItemData->MaxStackSize - Slot.Quantity;
			const int32 ToAdd = FMath::Min(SpaceLeft, RemainingQuantity);
			Slot.Quantity += ToAdd;
			RemainingQuantity -= ToAdd;
			OnInventoryUpdated.Broadcast();
			if (RemainingQuantity <= 0)
			{
				break;
			}
		}
	}
}

void UInventoryComponent::PlaceItemAt(UBaseItemData* ItemData, int32 Quantity, int32 SlotId)
{
	if (SlotId < 0 || SlotId >= InventoryGrid.Num()) return;

	FSlotData& Slot = InventoryGrid[SlotId];
	Slot.ItemData = ItemData;
	Slot.Quantity = FMath::Min(Quantity, ItemData->MaxStackSize);
	OnInventoryUpdated.Broadcast();
}

bool UInventoryComponent::TryAddItem(UBaseItemData* ItemData, int32 Quantity)
{
	if (!ItemData || Quantity <= 0) return false;

	for (FSlotData& Slot : InventoryGrid)
	{
		if (Slot.ItemData == ItemData && ItemData->bIsStackable)
		{
			TryStackItem(ItemData, Quantity);
			return true;
		}

		if (Slot.ItemData != ItemData)
		{
			if (const int32 EmptySlotIndex = FindFirstEmptySlot(); EmptySlotIndex != INDEX_NONE)
			{
				PlaceItemAt(ItemData, Quantity, EmptySlotIndex);
				return true;
			}
		}
	}
	return false;
}

