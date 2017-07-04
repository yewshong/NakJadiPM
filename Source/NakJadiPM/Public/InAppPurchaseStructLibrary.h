// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/NoExportTypes.h"
#include "InAppPurchaseStructLibrary.generated.h"
UENUM(BlueprintType)
enum class EStaffUpgradeType : uint8
{
	AddVPS,
	AddStartingGold,
	AddClick,
	HalveOpponentVPS,
};

UENUM(BlueprintType)
enum class ELevelEffect : uint8
{
	MultiplyAdd,
	AddByLevel,
};

USTRUCT(BlueprintType)
struct FStaffUpgrade : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EStaffUpgradeType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ELevelEffect LevelUpEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LevelEffectNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LevelStartEffectNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MedalStartCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float costMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ELevelEffect CostUpgradeEffect;
};

USTRUCT(BlueprintType)
struct FAllStaffUpgradeData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FStaffUpgrade> StaffUpgrades;

	FAllStaffUpgradeData()
	{
		StaffUpgrades = TArray<FStaffUpgrade>();
	}
};


USTRUCT(BlueprintType)
struct FStaffUpgradeRecord : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EStaffUpgradeType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NextValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int LevelUpCost;

};

USTRUCT(BlueprintType)
struct FConsumedRecord : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime UsedDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ProductID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TransactionID;
};

UENUM(BlueprintType)
enum class EProductReward : uint8
{
	NoAds,
	AddTenStars,
};


USTRUCT(BlueprintType)
struct FProductData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ProductID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Consumeable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText DisplayPrice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EProductReward Reward;
};

USTRUCT(BlueprintType)
struct FAllProductsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Version;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FProductData> Products;

	FAllProductsData()
	{
		Products = TArray<FProductData>();
	}
};

USTRUCT(BlueprintType)
struct FMedalAdsRecord : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime LastClaimTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan Cooldown;

	FMedalAdsRecord()
	{
		Cooldown = FTimespan(0, 20, 0);
		LastClaimTime = FDateTime::Now() - Cooldown;
	}
};


/**
 * 
 */
UCLASS()
class NAKJADIPM_API UInAppPurchaseStructLibrary : public UObject 
{
	GENERATED_BODY()
	
	
	
	
};
