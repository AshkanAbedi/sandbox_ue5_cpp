#pragma once

#include "CoreMinimal.h"
#include "SlotData.h"
#include "Widgets/SCompoundWidget.h"

struct FSlotData;

class SInventorySlot : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInventorySlot){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const FSlotData& InSlotData);

private:
	FSlateBrush EmptyBrush;
	FSlotData SlotData;
	
	const FSlateBrush* GetItemIconBrush() const;
	EVisibility GetQuantityTextVisibility() const;
	FText GetQuantityText() const;
};