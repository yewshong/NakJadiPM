// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
};
