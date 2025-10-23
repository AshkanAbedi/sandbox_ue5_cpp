#include "SInventoryGrid.h"
#include "SInventorySlot.h"
#include "SlateOptMacros.h"
#include "InventoryComponent.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SInventoryGrid::Construct(const FArguments& InArgs, UInventoryComponent* InInventoryComponent)
{
	InventoryComponent = InInventoryComponent;

	SAssignNew(GridPanel, SUniformGridPanel);

	ChildSlot
	[
		GridPanel.ToSharedRef()
	];

	RefreshGrid();

	if (InventoryComponent.IsValid())
	{
		InventoryComponent->OnInventoryUpdated.AddSP(this, &SInventoryGrid::RefreshGrid);
	}
}

void SInventoryGrid::RefreshGrid()
{
	if (!InventoryComponent.IsValid() || !GridPanel.IsValid())
	{
		return;
	}

	GridPanel->ClearChildren();

	const TArray<FSlotData>& InventorySlots = InventoryComponent->GetSlots();
	const int32 NumSlots = InventorySlots.Num();

	for (int32 i = 0; i < NumSlots; ++i)
	{
		constexpr int32 Columns = 6;
		const int32 Row = i / Columns;
		const int32 Column = i % Columns;

		GridPanel->AddSlot(Column, Row)
		[
			// For each slot in our data, create a new SInventorySlot widget.
			SNew(SInventorySlot, InventorySlots[i])
		];
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
