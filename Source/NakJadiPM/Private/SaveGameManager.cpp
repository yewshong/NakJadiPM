// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "SaveGameManager.h"

UCampaignSaveGame* SaveGameManager::CurrentSaveGame;

SaveGameManager::SaveGameManager()
{
	GetCampaignSaveGame();
}

SaveGameManager::~SaveGameManager()
{
}

UCampaignSaveGame* SaveGameManager::GetCampaignSaveGame()
{
	if(!CurrentSaveGame)
	{
		UCampaignSaveGame* LoadGameInstance = Cast<UCampaignSaveGame>(UGameplayStatics::CreateSaveGameObject(UCampaignSaveGame::StaticClass()));
		LoadGameInstance = Cast<UCampaignSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		CurrentSaveGame = LoadGameInstance;
	}
	return CurrentSaveGame;
}

bool SaveGameManager::UpdateSaveGame(UCampaignSaveGame* ToBeSavedGame)
{
	return UGameplayStatics::SaveGameToSlot(ToBeSavedGame, ToBeSavedGame->SaveSlotName, ToBeSavedGame->UserIndex);
}

bool SaveGameManager::SaveExists()
{
	if (CurrentSaveGame)
		return true;
	else
	{
		UCampaignSaveGame* saveGame = GetCampaignSaveGame();
		if (saveGame)
			return true;
	}

	return false;
}

