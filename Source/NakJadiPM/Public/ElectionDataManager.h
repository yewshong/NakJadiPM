// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ElectionDataManager.generated.h"


USTRUCT(BlueprintType)
struct FParlimentSeat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int VotersCount;

	FParlimentSeat()
	{
	}
};

USTRUCT(BlueprintType)
struct FState : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	int index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FParlimentSeat> ParlimentSeats;

	FState()
	{
		ParlimentSeats = TArray<FParlimentSeat>();
	}
};

USTRUCT(BlueprintType)
struct FElectionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FState> States;

	FElectionData()
	{
		Version = 0;
		States = TArray<FState>();
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
