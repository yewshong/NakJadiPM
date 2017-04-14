// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InAppPurchaseStructLibrary.h"
#include "CandidateDataManager.h"
#include "GameFramework/SaveGame.h"
#include "CampaignSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class NAKJADIPM_API UCampaignSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UCampaignSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString SaveSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int UserIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FCurrentCampaignData CampaignData;
};
