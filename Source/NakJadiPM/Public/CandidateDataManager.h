// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InAppPurchaseStructLibrary.h"
#include "ElectionDataManager.h"
#include "GameFramework/Actor.h"
#include "CandidateDataManager.generated.h"

USTRUCT(BlueprintType)
struct FSkillCostInfoTwo
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
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
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

UENUM(BlueprintType)
enum class EAdsRequestType : uint8
{
	Skill,
	Medal,
	Ballon,
};

UENUM(BlueprintType)
enum class EActiveSkillType : uint8
{
	DoubleClick,
	DoubleIdle,
};

USTRUCT(BlueprintType)
struct FActiveSkill : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EActiveSkillType SkillType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimespan Duration;
};

USTRUCT(BlueprintType)
struct FAllActiveSkillsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FActiveSkill> ActiveSkills;

	FAllActiveSkillsData()
	{
		ActiveSkills = TArray<FActiveSkill>();
	}
};

UENUM(BlueprintType)
enum class EBalloonEffectFactorType : uint8
{
	MultiplyCPS,
	MultiplyVPS,
	MultiplyByNumber,
	DivideByNumber,
};

UENUM(BlueprintType)
enum class EBalloonEffectType : uint8
{
	AddVote,
	AddGold,
	DivideOpponentVPS,
	MinusOpponentVoteCount,
	DisableOpponent,
};

USTRUCT(BlueprintType)
struct FBalloonSkill : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBalloonEffectType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBalloonEffectFactorType Factor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Number;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MinimumNumber;
};

USTRUCT(BlueprintType)
struct FAllBalloonSkillsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FBalloonSkill> BalloonSkills;

	FAllBalloonSkillsData()
	{
		BalloonSkills = TArray<FBalloonSkill>();
	}
};

USTRUCT(BlueprintType)
struct FActivatedSkill : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EActiveSkillType SkillType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime EndTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime StartTime;
};

USTRUCT(BlueprintType)
struct FCandidate : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> Skills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FText> SpecialSkills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString potraitPath;

	FCandidate()
	{
		Skills = TArray<FText>();
		SpecialSkills = TArray<FText>();
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
	ParliamentMember,
	PrimeMinister,
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
	FDateTime LastProcessTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCandidate SelectedCandidate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPoliticParty SelectedParty;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllActiveSkillsData ActiveSkillData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllBalloonSkillsData BalloonSkillData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllCandidatesData CandidatesData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllPoliticPartyData PoliticPartiesData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllStaffUpgradeData StaffUpgradesData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FParlimentSeatResult> SeatPossessionRecord;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSkillUpgradeInfo> SkillUpgradeRecord;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FActivatedSkill> ActivatedSkillRecord;

	FCurrentCampaignData()
	{
		Finished = false; FinishedReported = false;
		achievement = EAchievementEnum::Candidate;
		TimeRemaining = FTimespan(24,0,0);
		Balance = 0;
		ClickDamage = 0.1;
		VotesPerSecond = 0;
		StartTime = FDateTime::Now();
		EndTime = StartTime + FTimespan(24, 0, 0);
		LastProcessTime = FDateTime::Now();
		LastSavedTime = FDateTime::Now();
		ParlimentSeatsData = FAllParlimentSeatsData();
		StatesData = FAllStatesData();
		SkillsCostData = FAllSkillCostData();
		CandidatesData = FAllCandidatesData();
		PoliticPartiesData = FAllPoliticPartyData();
		SeatPossessionRecord = TArray<FParlimentSeatResult>();
		SkillUpgradeRecord = TArray<FSkillUpgradeInfo>();
		StaffUpgradesData = FAllStaffUpgradeData();
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
