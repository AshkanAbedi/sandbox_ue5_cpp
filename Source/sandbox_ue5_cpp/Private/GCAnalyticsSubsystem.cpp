// Fill out your copyright notice in the Description page of Project Settings.
#include "GCAnalyticsSubsystem.h"
#include "EngineUtils.h"
#include "Engine/Engine.h"
#include "UObject/UObjectGlobals.h"
#include "Serialization/ArchiveCountMem.h"

void UGCAnalyticsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	//PreGCDelegateHandle = FCoreUObjectDelegates::GetPreGarbageCollectDelegate().AddUObject(this, &UGCAnalyticsSubsystem::OnPreGarbageCollect);
	//PostGCDelegateHandle = FCoreUObjectDelegates::GetPostPurgeGarbageDelegate().AddUObject(this, &UGCAnalyticsSubsystem::OnPostGarbageCollect);
}

void UGCAnalyticsSubsystem::Deinitialize()
{
	FCoreUObjectDelegates::GetPostGarbageCollect().Remove(PreGCDelegateHandle);
	FCoreUObjectDelegates::GetPostGarbageCollect().Remove(PostGCDelegateHandle);
	Super::Deinitialize();
}

void UGCAnalyticsSubsystem::OnPreGarbageCollect()
{
	const UWorld* World = GetWorld();
	TArray<FString> AliveActorNames;
	
	if (!World && !GEngine)
	{
		return;
	}

	for (TActorIterator<AActor>It(World); It; ++It)
	{
		if (AActor* Actor = *It; IsValid(Actor))
		{
			++ObjCountPreGC;
			FArchiveCountMem ActorMemory(Actor, false);
			SIZE_T TotalMemoryBytes = ActorMemory.GetMax();
			TArray<UActorComponent*> Components;
			Actor->GetComponents(Components);
			for (const auto Component : Components)
			{
				if (IsValid(Component))
				{
					FArchiveCountMem ComponentMemory(Component, false);
					TotalMemoryBytes += ComponentMemory.GetMax();
				}
			}
			float MemKB = TotalMemoryBytes / 1024.0f;
			FString MemSizeString;
			if (MemKB >= 1000.0)
			{
				const double MemMB = MemKB / 1024.0;
				MemSizeString = FString::Printf(TEXT(" Size: %.2f MB"), MemMB);
			} else
			{
				MemSizeString = FString::Printf(TEXT(" Size: %.2f KB"), MemKB);
			}
			const FString ActorName = FString::Printf(TEXT("%s%s"), *Actor->GetName(), *MemSizeString);
			AliveActorNames.Add(ActorName);
		}
	}

	for (const FString& Name : AliveActorNames)
	{
		GEngine->AddOnScreenDebugMessage
		(
			-1,
			10.0f,
			FColor::Purple,
			Name
		);
	}

	GEngine->AddOnScreenDebugMessage
	(
		-1,
		10.0f,
		FColor::Green,
		FString::Printf(TEXT("Total actors alive on memory: %d"), ObjCountPreGC)
	);
	
}

void UGCAnalyticsSubsystem::OnPostGarbageCollect()
{
	const UWorld* World = GetWorld();

	if (!World && !GEngine)
	{
		return;
	}
	
	for (TActorIterator<AActor> It(World); It; ++It)
	{
		if (IsValid(*It))
		{
			++ObjCountPostGC;
		}
	}
	const int32 ObjectsGarbageCollected = ObjCountPostGC - ObjCountPreGC;
	
	GEngine->AddOnScreenDebugMessage
	(
		12345, // Unique key to overwrite message
		5.f,   // Duration in seconds
		FColor::Green,
		FString::Printf(TEXT("GC Cycle Ended. Objects collected: %d"), ObjectsGarbageCollected)
	);

	ObjCountPreGC = 0;
	ObjCountPostGC = 0;
}
