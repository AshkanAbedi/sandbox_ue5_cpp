#pragma once

#include "CoreMinimal.h"
#include "SlotData.generated.h"

class UItemData;

USTRUCT(BlueprintType)
struct FSlotData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	TObjectPtr<UItemData> ItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	int32 Quantity = 0;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	bool bIsRootSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	FIntPoint RootSlotCoordinate;*/
}; 