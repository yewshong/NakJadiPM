// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/NoExportTypes.h"
#include "InAppPurchaseStructLibrary.generated.h"
UENUM(BlueprintType)
enum class EStaffUpgradeType : uint8
{
	AddVPS,
	AddStartingGold,
	Add,
};

USTRUCT(BlueprintType)
struct FStaffUpgrade : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EStaffUpgradeType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StartingCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AddPerCentAfterUpgrade;
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
		int CurrentLevel;

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


/**
 * 
 */
UCLASS()
class NAKJADIPM_API UInAppPurchaseStructLibrary : public UObject 
{
	GENERATED_BODY()
	
	
	
	
};
