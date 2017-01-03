// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ElectionDataManager.generated.h"



USTRUCT(BlueprintType)
struct FState : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	int index;
	FString TexturePath;

	FState()
	{

	}
};
USTRUCT(BlueprintType)
struct FParlimentSeat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString State;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Count;

	FParlimentSeat()
	{
	}
};

USTRUCT(BlueprintType)
struct FAllParlimentSeatsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParlimentSeat> ParlimentSeats;

	FAllParlimentSeatsData()
	{
		ParlimentSeats = TArray<FParlimentSeat>();
	}
};



USTRUCT(BlueprintType)
struct FParlimentSeatResult 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Count;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentResult;

	FParlimentSeatResult()
	{
		currentResult = 0;
	}
};

USTRUCT(BlueprintType)
struct FElectionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParlimentSeatResult> ParlimentSeatsResult;

	FElectionData()
	{
		Version = 0;
		ParlimentSeatsResult = TArray<FParlimentSeatResult>();
	}
};


USTRUCT(BlueprintType)
struct FCurrentElectionResult : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParlimentSeat> ParlimentSeats;

	FCurrentElectionResult()
	{
		ParlimentSeats = TArray<FParlimentSeat>();
	}
};



UCLASS()
class NAKJADIPM_API AElectionDataManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElectionDataManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
