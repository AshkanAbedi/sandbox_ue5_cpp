// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemTypes.h"
#include "ItemData.generated.h"

UCLASS(BlueprintType)
class INVENTORYSYSTEM_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TSoftObjectPtr<UStaticMesh> WorldMesh;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data", meta = (ClampMin = 1, UIMin = 1))
	FIntPoint Dimensions = FIntPoint(1,1);*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Stacking")
	bool bIsStackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Stacking", meta = (EditCondition = "bIsStackable", ClampMin = 2, UIMin = 2))
	int32 MaxStackSize = 3;
};
