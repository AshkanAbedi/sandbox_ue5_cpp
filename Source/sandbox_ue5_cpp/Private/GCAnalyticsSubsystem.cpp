// Fill out your copyright notice in the Description page of Project Settings.

#include "GCAnalyticsSubsystem.h"
#include "Engine/Engine.h"
#include "UObject/UObjectGlobals.h"

void UGCAnalyticsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	GCDelegateHandle = FCoreUObjectDelegates::GetPostGarbageCollect().AddUObject(this, &UGCAnalyticsSubsystem::OnPostGarbageCollect);
}

void UGCAnalyticsSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::GetPostGarbageCollect().Remove(GCDelegateHandle);
	Super::Deinitialize();
}

void UGCAnalyticsSubsystem::OnPostGarbageCollect()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			54321, // Unique key to overwrite message
			5.f,   // Duration in seconds
			FColor::Yellow,
			TEXT("GC cycle completed (WorldSubsystem)")
		);
	}
}
