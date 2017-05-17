// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ElectionDataManager.generated.h"

USTRUCT(BlueprintType)
struct FPoliticParty : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString TexturePath;
};

USTRUCT(BlueprintType)
struct FAllPoliticPartyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FPoliticParty> Parties;

	FAllPoliticPartyData()
	{
		Parties = TArray<FPoliticParty>();
	}
};

USTRUCT(BlueprintType)
struct FState : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TexturePath;
};

USTRUCT(BlueprintType)
struct FAllStatesData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FState> States;

	FAllStatesData()
	{
		States = TArray<FState>();
	}
};

USTRUCT(BlueprintType)
struct FParlimentSeat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString State;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Count;

	bool operator<(const FParlimentSeat& rhs) const
	{
		return Count < rhs.Count;
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
	int Index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int OpponentIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpponentPossesion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpponentVPS;
			
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float possesion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PartiIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime OpponentDisableExpireTime;

	FParlimentSeatResult()
	{
		possesion = 0;
		OpponentPossesion = 0;
		OpponentDisableExpireTime = FDateTime::Now();
	}
};

/*USTRUCT(BlueprintType)
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
};*/


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
