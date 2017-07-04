// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InAppPurchaseStructLibrary.h"
#include "CandidateDataManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NJPUtilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NAKJADIPM_API UNJPUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		static const bool UseCheat = false;
		static const int TotalSeats = 222;
		static const int SeatsToWinElection = 112;
		static constexpr  float MaxOppoDamagePerLevel = 500.0f;
		static constexpr  float MinOppoDamage = 0.1f;
		static const int minSeatCount = 50;
		static const int SeatMultiplier = 3;

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static UTexture2D* LoadTextureFromPath(const FString& Path);
	
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static FString FormatStringToGoldFormat(int input);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static float ConvertTo2Decimals(float input);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static float CalculateCost(FSkillUpgradeInfo UpgradeInfo, FSkillCostInfo CostInfo);
	
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static FString GetVictoryEnumAsString(EAchievementEnum EnumValue);
	
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static FString ConstructPossestionText(int totalSeats, int currentSeats);
	
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static FString GetAchievementEnumAsString(EAchievementEnum EnumValue);
	
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static FText FormatBalloonDescription(FBalloonSkill BalloonSkill, FCurrentCampaignData CampaignData);
	
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static int CalculateBalloonEffect(FBalloonSkill BalloonSkill, FCurrentCampaignData CampaignData);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static int CalculateStaffLevelUpCost(FStaffUpgrade StaffUpgrade, int Level);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static float CalculateStaffEffectByLevel(FStaffUpgrade StaffUpgrade, int Level);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static FStaffUpgradeRecord CreateStaffUpgradeRecord(FStaffUpgrade StaffUpgrade, int Level);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static float ProcessGainsAfterBonus(float Gain, float Bonus);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static float RecalculateVPS(FCurrentCampaignData &CampaignData, float Bonus, int ClickSkillIndex);
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static float RecalculateClickGain(FCurrentCampaignData &CampaignData,float Bonus, int ClickSkillIndex);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static float RecalculateOpponentVPS(int Seatnumber, int MalaysiaLevel, float HalvePercent);
	
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static void RecalculateSeatOpponentVPS(int Seatnumber, int MalaysiaLevel, float HalvePercent, FParlimentSeatResult &ParliamentSeatResult);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static void AddStateSeatAndRecalculateSeatVoteCount(int SeatNumber, FParlimentSeatResult &ParliamentSeatResult, FParlimentSeat &ParliamentSeatData);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static int CalculateParlimentSeatCount(int SeatNumber);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static int CalculateElectionWon(FCurrentCampaignData CampaignData);	

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static int CalculateSeatsWon(FCurrentCampaignData CampaignData);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static int CalculateMedalsMultiplier(int ElectionWon, int Bonus);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static int CalculateMedalsEarned(int MedalMultiplier, int SeatsWon);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static float LerpByRange(float Desired, float Current, FTimespan DisplayTimeSpan, FDateTime StartTime);
	
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static float Interpolate(float Desired, float Current, float speed);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static void GetCurrentSeatPossesionFromSeat(float &playerPossesion, float &opponentPossesion, int &count, FParlimentSeatResult ParliamentSeatResult);
	
	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static FText ConvertFloatToDisplayText(float Number);

	UFUNCTION(BlueprintCallable, Category = "NJPUtility")
		static void ShowFacebookPage();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NJPUtility")
		static bool IsStateSeatDone(FParlimentSeatResult ParliamentSeatResult);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NJPUtility")
		static int CurrentStateSeatIndex(FParlimentSeatResult ParliamentSeatResult);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NJPUtility")
	static FString GetFloatAsStringWithPrecision(float TheFloat, int32 Precision, bool IncludeLeadingZero = true);
};
