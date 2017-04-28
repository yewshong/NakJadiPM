// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "NJPUtilityFunctionLibrary.h"





UTexture2D* UNJPUtilityFunctionLibrary::LoadTextureFromPath(const FString& Path)
{
	if (Path.IsEmpty()) return NULL;

	/*FString PathToLoad = "/Game/Textures/YourStructureHere";
	UTexture2D* tmpTexture = LoadTextureFromPath(PathToLoad);*/

	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(Path)));
}


FString UNJPUtilityFunctionLibrary::FormatStringToGoldFormat(int input)
{
	return FString::FromInt(input);
}

float UNJPUtilityFunctionLibrary::ConvertTo2Decimals(float input)
{
	int multiply = (int)(FMath::RoundToFloat(input / 0.01));
	float total = (int)(FMath::RoundToFloat(input / 0.01)) * 0.01f;
	return ((int)(FMath::RoundToFloat(input/0.01))) * 0.01f;
}

float UNJPUtilityFunctionLibrary::CalculateCost(FSkillUpgradeInfo UpgradeInfo, FSkillCostInfo CostInfo)
{ 
	float Cost = CostInfo.StartingCost;
	for (int i = 0; i < UpgradeInfo.Level; i++)
	{
		Cost += Cost * CostInfo.AddPerCentAfterUpgrade / 100;
	}
	if (Cost < 100)
		return ConvertTo2Decimals(Cost);
	else
		return FMath::FloorToFloat(Cost);
}

FString UNJPUtilityFunctionLibrary::GetVictoryEnumAsString(EAchievementEnum EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAchievementEnum"), true);
	if (!EnumPtr) return FString("Invalid");

	return EnumPtr->GetEnumName((int32)EnumValue);
}

FString UNJPUtilityFunctionLibrary::ConstructPossestionText(int totalSeats, int currentSeats)
{
	return FString::FromInt(currentSeats) + " / " + FString::FromInt(totalSeats);
}

FString UNJPUtilityFunctionLibrary::GetAchievementEnumAsString(EAchievementEnum EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAchievementEnum"), true);
	if (!EnumPtr) return FString("Invalid");

	return EnumPtr->GetEnumName((int32)EnumValue); 
}


FText UNJPUtilityFunctionLibrary::FormatBalloonDescription(FBalloonSkill BalloonSkill, FCurrentCampaignData CampaignData)
{
	return FText::Format(BalloonSkill.Description, CalculateBalloonEffect(BalloonSkill,CampaignData));
}

int UNJPUtilityFunctionLibrary::CalculateBalloonEffect(FBalloonSkill BalloonSkill, FCurrentCampaignData CampaignData)
{
	switch (BalloonSkill.Factor)
	{
	case EBalloonEffectFactorType::DivideByNumber: 
		return BalloonSkill.Number;
		break;
	case EBalloonEffectFactorType::MultiplyByNumber:
		return BalloonSkill.Number;
		break;
	case EBalloonEffectFactorType::MultiplyCPS:
		return BalloonSkill.Number * CampaignData.ClickDamage;
		break;
	case EBalloonEffectFactorType::MultiplyVPS: 
		return BalloonSkill.Number * CampaignData.VotesPerSecond;
		break;
	}
	return 0;
}


int UNJPUtilityFunctionLibrary::CalculateStaffLevelUpCost(FStaffUpgrade StaffUpgrade, int Level)
{

	if (Level == 0)
		return StaffUpgrade.MedalStartCost;

	switch (StaffUpgrade.CostUpgradeEffect)
	{
	case ELevelEffect::AddByLevel: return (int)( StaffUpgrade.MedalStartCost + (StaffUpgrade.costMultiplier*(Level-1))); break;
		case ELevelEffect::MultiplyAdd:
			float result = StaffUpgrade.MedalStartCost;
			for (int i = 1; i < Level; i++)
			{
				result += result * StaffUpgrade.costMultiplier;
			}
			return (int)result;
	}
	return 1;
}

float UNJPUtilityFunctionLibrary::CalculateStaffEffectByLevel(FStaffUpgrade StaffUpgrade, int Level)
{
	if (Level == 0)
		return 0;

	switch (StaffUpgrade.LevelUpEffect) 
	{
	case ELevelEffect::AddByLevel: 
			return FMath::CeilToInt(StaffUpgrade.LevelStartEffectNumber + (StaffUpgrade.LevelEffectNumber*(Level-1))); break;
	case ELevelEffect::MultiplyAdd:
		
		float result = StaffUpgrade.LevelStartEffectNumber;
		for (int i = 1; i < Level; i++)
		{
			result += result * StaffUpgrade.LevelEffectNumber;
		}
		return FMath::CeilToInt(result);
		
	}
	return 1; 
}

FStaffUpgradeRecord UNJPUtilityFunctionLibrary::CreateStaffUpgradeRecord(FStaffUpgrade StaffUpgrade,int Level)
{
	FStaffUpgradeRecord upgradeRecord = FStaffUpgradeRecord();
	upgradeRecord.Name = StaffUpgrade.Name;
	upgradeRecord.Type = StaffUpgrade.Type;
	upgradeRecord.CurrentLevel = Level;
	upgradeRecord.CurrentValue = CalculateStaffEffectByLevel(StaffUpgrade, upgradeRecord.CurrentLevel);
	upgradeRecord.NextValue = CalculateStaffEffectByLevel(StaffUpgrade, upgradeRecord.CurrentLevel + 1);
	upgradeRecord.LevelUpCost = CalculateStaffLevelUpCost(StaffUpgrade, upgradeRecord.CurrentLevel);
	return upgradeRecord;
}


float UNJPUtilityFunctionLibrary::ProcessGainsAfterBonus(float Gain, float Bonus)
{
	if (Bonus > 0)
		return Gain += Gain * (Bonus / 100);
	else
		return Gain;
}


float UNJPUtilityFunctionLibrary::RecalculateVPS(FCurrentCampaignData &CampaignData, float Bonus,int ClickSkillIndex)
{
	float result = 0;
	for (int i = 0;  i < CampaignData.SkillUpgradeRecord.Num(); i++)
	{
		if(i != ClickSkillIndex)
		result += CampaignData.SkillUpgradeRecord[i].Level * CampaignData.SkillsCostData.SkillCosts[i].Damage;
	}
	
	return ProcessGainsAfterBonus(result, Bonus);
}

float UNJPUtilityFunctionLibrary::RecalculateClickGain(FCurrentCampaignData &CampaignData, float Bonus, int ClickSkillIndex)
{
	if (CampaignData.SkillUpgradeRecord.IsValidIndex(ClickSkillIndex) &&
		CampaignData.SkillsCostData.SkillCosts.IsValidIndex(ClickSkillIndex))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Gain : %f"), CampaignData.SkillsCostData.SkillCosts[ClickSkillIndex].Damage * CampaignData.SkillUpgradeRecord[ClickSkillIndex].Level));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Bonus : %f"), Bonus));
		float ClickDamage = FMath::Max(1.0f, CampaignData.SkillsCostData.SkillCosts[ClickSkillIndex].Damage * CampaignData.SkillUpgradeRecord[ClickSkillIndex].Level);
		
		if (UseCheat)
			ClickDamage = FMath::Max(50000.0f, ClickDamage);
		
		return ProcessGainsAfterBonus(ClickDamage, Bonus);

	}

	return 1;
}

float UNJPUtilityFunctionLibrary::RecalculateOpponentVPS(int SeatNumber, int MalaysiaLevel)
{
	if (SeatNumber == 0)
		return MinOppoDamage;
	else
	{
		return MinOppoDamage + (MalaysiaLevel * SeatNumber * MaxOppoDamagePerLevel / TotalSeats);
	}
}

int UNJPUtilityFunctionLibrary::CalculateElectionWon(FCurrentCampaignData CampaignData)
{
	int Result = CampaignData.SeatPossessionRecord.Num() / TotalSeats;
	if (CampaignData.SeatPossessionRecord.Num() % TotalSeats >= SeatsToWinElection)
	{
		Result += 1;
	}
	return Result;
}

int UNJPUtilityFunctionLibrary::CalculateSeatsWon(FCurrentCampaignData CampaignData)
{
	if (CampaignData.SeatPossessionRecord.Num() == 0)
		return 0;

	FParlimentSeatResult LastSeatResult = CampaignData.SeatPossessionRecord.Last();
	if (LastSeatResult.possesion * 100 / CampaignData.ParlimentSeatsData.ParlimentSeats[LastSeatResult.Index].Count > 50)
	{
		return CampaignData.SeatPossessionRecord.Num();
	}

	return CampaignData.SeatPossessionRecord.Num()-1;
}

int UNJPUtilityFunctionLibrary::CalculateMedalsMultiplier(int ElectionWon, int Bonus)
{
	return 1 + ElectionWon + Bonus;
}

int UNJPUtilityFunctionLibrary::CalculateMedalsEarned(int MedalMultiplier, int SeatsWon)
{
	return MedalMultiplier * SeatsWon;
}


float UNJPUtilityFunctionLibrary::LerpByRange(float Desired, float Current, FTimespan DisplayTimeSpan, FDateTime StartTime)
{
	if (Desired == Current ||
		FDateTime::Now() > StartTime + DisplayTimeSpan)
		return Desired;

	FTimespan diff = FDateTime::Now() - StartTime;
	if (DisplayTimeSpan.GetTotalSeconds() != 0)
	{
		float alpha = FMath::Min(1.0, (double)diff.GetTotalSeconds() / DisplayTimeSpan.GetTotalSeconds());
		return FMath::Lerp(Current, Desired, alpha);
	}
	//
	return Desired;
}