// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InAppPurchaseStructLibrary.h"
#include "GameFramework/SaveGame.h"
#include "ProductsSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class NAKJADIPM_API UProductsSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UProductsSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString SaveSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int UserIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int Medal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool NoAds;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool NoAdsActivated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<FConsumedRecord> ConsumedRecords;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FAllProductsData AllProductsData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<FStaffUpgradeRecord> staffUpgradeRecords;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FMedalAdsRecord MedalAdsRecord;

	UFUNCTION()
		void UpdateProductInfo(FString &ID, FString &DisplayPrice);

private:
	int StartMedal = 20;
};
