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