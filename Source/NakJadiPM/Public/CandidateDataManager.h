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
	int SkillStage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartingCost;
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AddPerCentAfterUpgrade;
};

USTRUCT(BlueprintType)
struct FAllSkillCostData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FSkillCostInfo> SkillCosts;

	FAllSkillCostData()
	{
		SkillCosts = TArray<FSkillCostInfo>();
	}
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
struct FSkillUpgradeInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

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

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EAchievementEnum : uint8
{
	Candidate,
	//StateAssemblyRepresentatives,
	//MenteriBesar,
	ParliamentMember,
	PrimeMinister,
	TwoThirdMajority,
	FullWin
};


USTRUCT(BlueprintType)
struct FCurrentCampaignData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Finished; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FinishedReported;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAchievementEnum achievement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime StartTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime EndTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime LastSavedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCandidate SelectedCandidate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan TimeRemaining;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Balance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ClickDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VotesPerSecond;

	//add state
	//add skill upgrade formula? 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAllParlimentSeatsData ParlimentSeatsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllStatesData StatesData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllSkillCostData SkillsCostData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FParlimentSeatResult> SeatPossessionRecord;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSkillUpgradeInfo> SkillUpgradeRecord;

	FCurrentCampaignData()
	{
		Finished = false; FinishedReported = false;
		achievement = EAchievementEnum::Candidate;
		TimeRemaining = FTimespan(24,0,0);
		Balance = 0;
		ClickDamage = 0.1;
		VotesPerSecond = 0;
		StartTime = FDateTime::UtcNow();
		EndTime = StartTime + FTimespan(24, 0, 0);
		LastSavedTime = FDateTime::UtcNow();
		ParlimentSeatsData = FAllParlimentSeatsData();
		StatesData = FAllStatesData();
		SkillsCostData = FAllSkillCostData();
		SeatPossessionRecord = TArray<FParlimentSeatResult>();
		SkillUpgradeRecord = TArray<FSkillUpgradeInfo>();
	}

	static bool VerifyCaimpagnData(FCurrentCampaignData Data)
	{
		return true;
	}
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
