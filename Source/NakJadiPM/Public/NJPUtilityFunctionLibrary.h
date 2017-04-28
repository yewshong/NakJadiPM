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
		static constexpr  float MaxOppoDamagePerLevel = 100.0f;
		static constexpr  float MinOppoDamage = 0.1f;

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
		static float RecalculateOpponentVPS(int Seatnumber, int MalaysiaLevel);

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
};
