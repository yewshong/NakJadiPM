// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CampaignSaveGame.h"
#include "Kismet/GameplayStatics.h"
/**
 * 
 */
class NAKJADIPM_API SaveGameManager
{
public:
	SaveGameManager();
	~SaveGameManager();

	static UCampaignSaveGame* CurrentSaveGame;
	static UCampaignSaveGame* GetCampaignSaveGame();
	static bool UpdateSaveGame(UCampaignSaveGame* ToBeSavedGame);

	static bool SaveExists();
	static bool CampaignFinished();
	static bool UpdateAndSaveCampaignData();
};
