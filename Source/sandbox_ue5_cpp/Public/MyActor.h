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

USTRUCT(BlueprintType)
struct FTestStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECalcType CalcType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumB;
};

UCLASS()
class SANDBOX_UE5_CPP_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyActor();
	virtual void BeginPlay() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPrintStructDelegate, const FTestStruct&, TestStruct, const float, PrintDuration);

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnPrintStructDelegate OnPrintStruct;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FTestStruct MyStruct;

	void SetupInput();

	void PressedH();

	UFUNCTION()
	void PrintHello();

	UFUNCTION()
	void PrintStruct(const FTestStruct& TestStruct, const float PrintDuration);

protected:

private:	
	
};
