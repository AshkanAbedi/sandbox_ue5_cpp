// Fill out your copyright notice in the Description page of Project Settings.
#include "GCAnalyticsSubsystem.h"
#include "EngineUtils.h"
#include "Engine/Engine.h"
#include "UObject/UObjectGlobals.h"
#include "ProfilingDebugging/ResourceSize.h"

void UGCAnalyticsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	PreGCDelegateHandle = FCoreUObjectDelegates::GetPreGarbageCollectDelegate().AddUObject(this, &UGCAnalyticsSubsystem::OnPreGarbageCollect);
	PostGCDelegateHandle = FCoreUObjectDelegates::GetPostPurgeGarbageDelegate().AddUObject(this, &UGCAnalyticsSubsystem::OnPostGarbageCollect);
}

void UGCAnalyticsSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::GetPostGarbageCollect().Remove(PreGCDelegateHandle);
	FCoreUObjectDelegates::GetPostGarbageCollect().Remove(PostGCDelegateHandle);
	Super::Deinitialize();
}

void UGCAnalyticsSubsystem::OnPreGarbageCollect()
{
	int32 ActorCount = 0;
	TArray<FString> AliveActorNames;
	const UWorld* World = GetWorld();
	FResourceSizeEx Size(EResourceSizeMode::EstimatedTotal);

	if (!World)
	{
		return;
	}

	for (TActorIterator<AActor>It(World); It; ++It)
	{
		if (AActor* Actor = *It; IsValid(Actor))
		{
			++ActorCount;
			Actor->GetResourceSizeEx(Size);
			const double MemKB = static_cast<double>(Size.GetTotalMemoryBytes()) / 1024.0;
			FString MemSize;
			if (MemKB >= 1000.0)
			{
				const double MemMB = MemKB / 1024.0;
				MemSize = FString::Printf(TEXT(" Size: %.2f MB"), MemMB);
			} else
			{
				MemSize = FString::Printf(TEXT(" Size: %.2f KB"), MemKB);
			}
			const FString ActorName = FString::Printf(TEXT("%s%s"), *Actor->GetName(), *MemSize);
			AliveActorNames.Add(ActorName);
		}
	}

	if (GEngine)
	{
		for (const FString& Name : AliveActorNames)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				10.0f,
				FColor::Purple,
				Name
			);
		}
	}
}

void UGCAnalyticsSubsystem::OnPostGarbageCollect()
{

	int32 CountAfter = 0;
	for (TObjectIterator<UObject> It; It; ++It)
	{
		if (!It->IsGarbageEliminationEnabled())
		{
			++CountAfter;
		}
	}
	int32 ObjectsGarbageCollected = ObjCountPreGC - CountAfter;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			12345, // Unique key to overwrite message
			5.f,   // Duration in seconds
			FColor::Green,
			FString::Printf(TEXT("GC Cycle Ended. Objects after GC: %d. Objects collected: %d"), CountAfter, ObjectsGarbageCollected)
		);
	}
}
