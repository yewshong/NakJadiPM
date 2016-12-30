// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

//#include "ElectionDataStruct.Generated.h"


/*USTRUCT(BlueprintType)
struct FState
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name;
	int index;
	
	FState()
	{
	}
};

USTRUCT(BlueprintType)
struct FParlimentSeat
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name;
	UPROPERTY()
	uint32 VotersCount;

	UPROPERTY()
	FState State;
	
	FParlimentSeat()
	{
	}
};


USTRUCT(BlueprintType)
struct FElectionData
{
	GENERATED_BODY()

		UPROPERTY()
		float Version;

	UPROPERTY()
		TArray<FParlimentSeat> ParlimentSeats;

	FElectionData()
	{
		Version = 0;
		ParlimentSeats = TArray<FParlimentSeat>();
	}
};*/

class NAKJADIPM_API ElectionDataStruct
{
public:
	ElectionDataStruct();
	~ElectionDataStruct();
};
