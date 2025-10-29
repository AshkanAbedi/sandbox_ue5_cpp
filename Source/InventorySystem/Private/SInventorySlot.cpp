#include "SInventorySlot.h"
#include "SlateOptMacros.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBorder.h"
#include "ItemData.h"
#include "SlotData.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SInventorySlot::Construct(const FArguments& InArgs, const FSlotData& InSlotData)
{
	SlotData = InSlotData;
	if (SlotData.ItemData && SlotData.ItemData->Icon.IsValid())
	{
		EmptyBrush.SetResourceObject(SlotData.ItemData->Icon.LoadSynchronous());
	}

	ChildSlot
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	[
		SNew(SBox)
		.WidthOverride(512.f)
		.HeightOverride(512.f)
		[
			SNew(SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder")) // A default engine brush
			.Padding(4.f)
			[
				SNew(SOverlay) // Overlay allows stacking widgets on top of each other.
			
			// Layer 0: The item icon
				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(SImage)
					.Image(this, &SInventorySlot::GetItemIconBrush)
				]

			// Layer 1: The quantity text
				+ SOverlay::Slot()
				.HAlign(HAlign_Right)
				.VAlign(VAlign_Bottom)
				[
					SNew(STextBlock)
					.Text(this, &SInventorySlot::GetQuantityText)
					.Visibility(this, &SInventorySlot::GetQuantityTextVisibility)
					.Font(FCoreStyle::Get().GetFontStyle("EmbossedText"))
					.ShadowOffset(FVector2D(1, 1))
				]
			]
		]
	];
}

const FSlateBrush* SInventorySlot::GetItemIconBrush() const
{
	return (SlotData.ItemData && SlotData.ItemData->Icon.IsValid()) ? &EmptyBrush : FStyleDefaults::GetNoBrush();
}

EVisibility SInventorySlot::GetQuantityTextVisibility() const
{
	if (SlotData.ItemData && SlotData.ItemData->bIsStackable && SlotData.Quantity > 1)
	{
		return EVisibility::Visible;
	}
	return EVisibility::Collapsed;
}

FText SInventorySlot::GetQuantityText() const
{
	if (SlotData.Quantity > 0)
	{
		return FText::AsNumber(SlotData.Quantity);
	}
	return FText::GetEmpty();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
