// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

struct FSlotData;
class UItemData;

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Grid", meta = (ClampMin = 1, UIMin = 1))
	int32 GridRows = 6;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Grid", meta = (ClampMin = 1, UIMin = 1))
	int32 GridColumns = 2;
	
	FOnInventoryUpdated OnInventoryUpdated;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UItemData* ItemData, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool UseItem(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 GetCapacity() const { return GridRows * GridColumns; }

	UFUNCTION(BlueprintCallable, Category="Inventory")
	const TArray<FSlotData>& GetSlots() const { return InventoryGrid; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<FSlotData> InventoryGrid;
	
	void InitializeGrid();
	int32 CountEmptySlots() const;
	int32 FindFirstEmptySlot() const;
	int32 StackIntoExisting(UItemData* ItemData, int32 Quantity);
	int32 FillEmptySlots(UItemData* ItemData, int32 Quantity);
};
