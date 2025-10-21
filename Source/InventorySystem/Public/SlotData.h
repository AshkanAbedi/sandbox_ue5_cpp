#pragma once

#include "CoreMinimal.h"

class UBaseItemData;

USTRUCT(BlueprintType)
struct FSlotData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	TObjectPtr<UBaseItemData> ItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	int32 Quantity = 0;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	bool bIsRootSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	FIntPoint RootSlotCoordinate;*/
}; 