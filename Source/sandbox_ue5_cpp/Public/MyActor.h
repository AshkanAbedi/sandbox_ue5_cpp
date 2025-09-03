// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UENUM(BlueprintType)
enum class ECalcType : uint8
{
	Add UMETA(DisplayName = "Add"),
	Subtract UMETA(DisplayName = "Subtract"),
	Multiply UMETA(DisplayName = "Multiply"),
	Divide UMETA(DisplayName = "Divide")
};

UCLASS()
class SANDBOX_UE5_CPP_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyActor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPrintHelloDelegate);

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnPrintHelloDelegate OnPrintHello;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calculation")
	ECalcType CalcType;

	void SetupInput();

	void PressedH();

	UFUNCTION()
	void PrintHello();

protected:

private:	
	
};
