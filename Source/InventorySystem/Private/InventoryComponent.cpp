// Fill out your copyright notice in the Description page of Project Settings.
#include "InventoryComponent.h"
#include "ItemData.h"
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

int32 UInventoryComponent::StackIntoExisting(UItemData* ItemData, int32 Quantity)
{
	if (!ItemData || !ItemData->bIsStackable || Quantity <= 0) return Quantity;

	int32 RemainingQuantity = Quantity;
	
	for (FSlotData& Slot : InventoryGrid)
	{
		if (RemainingQuantity <= 0) break;
		
		if (Slot.ItemData == ItemData && Slot.Quantity < ItemData->MaxStackSize)
		{
			const int32 SpaceLeft = ItemData->MaxStackSize - Slot.Quantity;
			const int32 ToAdd = FMath::Min(SpaceLeft, RemainingQuantity);
			Slot.Quantity += ToAdd;
			RemainingQuantity -= ToAdd;
			OnInventoryUpdated.Broadcast();
		}
	}
	
	return RemainingQuantity;
}

int32 UInventoryComponent::FillEmptySlots(UItemData* ItemData, int32 Quantity)
{
	if (!ItemData || Quantity < 0) return Quantity;

	int32 RemainingQuantity = Quantity;

	int32 EmptySlotIndex = FindFirstEmptySlot();

	if (EmptySlotIndex != INDEX_NONE && RemainingQuantity > 0)
	{
		FSlotData& Slot = InventoryGrid[EmptySlotIndex];
		if (ItemData->bIsStackable)
		{
			const int32 ToAdd = FMath::Min(ItemData->MaxStackSize, RemainingQuantity);
			Slot.ItemData = ItemData;
			Slot.Quantity = ToAdd;
			RemainingQuantity -= ToAdd;
			OnInventoryUpdated.Broadcast();
		}
		else 
		{
			Slot.ItemData = ItemData;
			Slot.Quantity = 1;
			RemainingQuantity -= 1;
			OnInventoryUpdated.Broadcast();
		}
	}
	return RemainingQuantity;
}

bool UInventoryComponent::AddItem(UItemData* ItemData, int32 Quantity)
{
	if (!ItemData || Quantity <= 0) return false;

	int32 RemainingQuantity = Quantity;

	if (ItemData->bIsStackable) RemainingQuantity = StackIntoExisting(ItemData, RemainingQuantity);

	RemainingQuantity = FillEmptySlots(ItemData, RemainingQuantity);

	if (RemainingQuantity != Quantity)
	{
		OnInventoryUpdated.Broadcast();
	}
	return RemainingQuantity == 0;
}

bool UInventoryComponent::UseItem(int32 SlotIndex)
{
	if (!InventoryGrid.IsValidIndex(SlotIndex) || InventoryGrid[SlotIndex].ItemData == nullptr) return false;

	FSlotData& Slot = InventoryGrid[SlotIndex];

	Slot.Quantity--;

	if (Slot.Quantity <= 0)
	{
		Slot.ItemData = nullptr;
	}
	OnInventoryUpdated.Broadcast();
	return true;
}

