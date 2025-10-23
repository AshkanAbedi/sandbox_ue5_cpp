#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlotData.h"

class SInventorySlot : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInventorySlot){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const FSlotData& InSlotData);
	
protected:
private:

	FSlateBrush EmptyBrush;
	FSlotData SlotData;

	const FSlateBrush* GetItemIconBrush() const;
	EVisibility GetQuantityTextVisibility() const;
	FText GetQuantityText() const;
};