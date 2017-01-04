// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ElectionDataManager.h"
#include "GameFramework/Actor.h"
#include "CandidateDataManager.generated.h"

USTRUCT(BlueprintType)
struct FSkillCostInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SkillLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StartingCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AddPerCentAfterUpgrade;
};


USTRUCT(BlueprintType)
struct FCandidateSkills : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
};

USTRUCT(BlueprintType)
struct FCurrentCampaignSkillInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int upgradeLevel;

};

USTRUCT(BlueprintType)
struct FCandidate : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Skills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString potraitPath;

	FCandidate()
	{
		Skills = TArray<FString>();
	}
};

USTRUCT(BlueprintType)
struct FAllCandidatesData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FCandidate> AllCandidates;

	FAllCandidatesData()
	{
		AllCandidates = TArray<FCandidate>();
	}
};

USTRUCT(BlueprintType)
struct FCurrentCampaignData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Finished;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime StartTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCandidate SelectedCandidate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCurrentCampaignSkillInfo> CurrentCampaignSkills;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int balance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCurrentElectionResult CurrentElectionResult;

};


UCLASS()
class NAKJADIPM_API ACandidateDataManager : public AActor
{
	GENERATED_BODY()
	 
public:	

	// Sets default values for this actor's properties
	ACandidateDataManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
};
