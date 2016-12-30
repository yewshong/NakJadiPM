// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "CandidateDataStruct.Generated.h"

/**
 * 
 */

/*USTRUCT(BlueprintType)
struct FCandidateSkills
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name;
	UPROPERTY()
	FString Damage;

	UPROPERTY()
	int32 level;
	UPROPERTY()
	int32 Cost;

	FCandidateSkills()
	{
	}
};

USTRUCT(BlueprintType)
struct FCandidate
{
	GENERATED_BODY()
		
	UPROPERTY()
	TArray<FCandidateSkills> Skills;   

	FCandidate()
	{
		Skills = TArray<FCandidateSkills>();
	}
};

USTRUCT(BlueprintType)
struct FAllCandidatesData
{
	GENERATED_BODY()

	UPROPERTY()
	float Version;

	UPROPERTY()
	TArray<FCandidate> AllCandidates;

	FAllCandidatesData()
	{
		Version = 0;
		AllCandidates = TArray<FCandidate>();
	}
};*/

class NAKJADIPM_API CandidateDataStruct
{
public:
	CandidateDataStruct();
	~CandidateDataStruct();
};
