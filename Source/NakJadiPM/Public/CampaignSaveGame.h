// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
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

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FCurrentCampaignData CampaignData;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	bool finished;
	
	UCampaignSaveGame();
};
