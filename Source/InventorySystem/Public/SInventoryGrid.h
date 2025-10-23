#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UInventoryComponent;
class SUniformGridPanel;

class SInventoryGrid : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInventoryGrid){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UInventoryComponent* InInventoryComponent);
	void RefreshGrid();

private:
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;
	TSharedPtr<SUniformGridPanel> GridPanel;
};