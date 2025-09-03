// Fill out your copyright notice in the Description page of Project Settings.
#include "MyActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;
	OnPrintHello.AddDynamic(this, &AMyActor::PrintHello);
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	SetupInput();
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::SetupInput()
{
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	InputComponent->BindKey(EKeys::H, IE_Pressed, this, &AMyActor::PressedH);
}

void AMyActor::PressedH()
{
	OnPrintHello.Broadcast();
}

void AMyActor::PrintHello()
{
	UKismetSystemLibrary::PrintString(this, TEXT("Hello World!"), true, true, FColor::Red, 5, TEXT("None"));
}

