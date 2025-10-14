// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppMemberFunctionMayBeConst

#include "MyActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = false;
	OnPrintStruct.AddDynamic(this, &AMyActor::PrintStruct);
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	SetupInput();
}

void AMyActor::SetupInput()
{
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	InputComponent->BindKey(EKeys::H, IE_Pressed, this, &AMyActor::PressedH);
}

void AMyActor::PressedH()
{
	OnPrintStruct.Broadcast(MyStruct, 5.0f);
}

void AMyActor::PrintHello()
{
	UKismetSystemLibrary::PrintString(this, TEXT("Hello World!"), true, true, FColor::Red, 5, TEXT("None"));
}

void AMyActor::PrintStruct(const FTestStruct& TestStruct, const float PrintDuration)
{
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("CalcType: %d, NumA: %d, NumB: %d"), static_cast<int32>(TestStruct.CalcType), TestStruct.NumA, TestStruct.NumB), true, true, FColor::Green, PrintDuration, TEXT("None"));
}

