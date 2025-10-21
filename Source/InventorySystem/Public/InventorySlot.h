#pragma once

#include "CoreMinimal.h"

class UBaseItemData;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	TObjectPtr<UBaseItemData> ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	int32 Quantity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	bool bIsRootSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	FIntPoint RootSlotCoordinate;
}; 