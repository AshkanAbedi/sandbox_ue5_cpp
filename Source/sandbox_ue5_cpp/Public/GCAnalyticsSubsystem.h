// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GCAnalyticsSubsystem.generated.h"

UCLASS()
class SANDBOX_UE5_CPP_API UGCAnalyticsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void OnPreGarbageCollect();
	void OnPostGarbageCollect();

	int32 ObjCountPreGC;
	int32 ObjCountPostGC;
	FDelegateHandle PreGCDelegateHandle;
	FDelegateHandle PostGCDelegateHandle;
	
};
