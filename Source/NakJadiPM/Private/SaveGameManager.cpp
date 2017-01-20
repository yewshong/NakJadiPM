// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "SaveGameManager.h"

ASaveGameManager::ASaveGameManager()
{
	GetCampaignSaveGame();
}

// Called when the game starts or when spawned
void ASaveGameManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASaveGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UCampaignSaveGame* ASaveGameManager::GetCampaignSaveGame()
{
	if(!CurrentSaveGame)
	{
		UCampaignSaveGame* LoadGameInstance = Cast<UCampaignSaveGame>(UGameplayStatics::CreateSaveGameObject(UCampaignSaveGame::StaticClass()));
		LoadGameInstance = Cast<UCampaignSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		CurrentSaveGame = LoadGameInstance;
	}
	return CurrentSaveGame;
}

bool ASaveGameManager::UpdateSaveGame(UCampaignSaveGame* ToBeSavedGame)
{
	if (UGameplayStatics::SaveGameToSlot(ToBeSavedGame, ToBeSavedGame->SaveSlotName, ToBeSavedGame->UserIndex))
	{
		CurrentSaveGame = ToBeSavedGame;
		return true;
	}
	else
		return false;
}

bool ASaveGameManager::SaveExists()
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

bool ASaveGameManager::CreateNewAndSaveGame(FCurrentCampaignData CampaignData)
{
	UCampaignSaveGame* SaveGameInstance = Cast<UCampaignSaveGame>(UGameplayStatics::CreateSaveGameObject(UCampaignSaveGame::StaticClass()));
	SaveGameInstance->CampaignData = CampaignData;
	return UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

bool ASaveGameManager::DeleteSaveGame()
{
	GetCampaignSaveGame();
	if (!CurrentSaveGame)
		return true;

	if (!UGameplayStatics::DoesSaveGameExist(CurrentSaveGame->SaveSlotName, CurrentSaveGame->UserIndex))
		return true;

	if (UGameplayStatics::DeleteGameInSlot(CurrentSaveGame->SaveSlotName, CurrentSaveGame->UserIndex))
	{

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("DeleteGameInSlot success"));
		return true;
	}
	else
	{

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("DeleteGameInSlot failed"));
		return false;
	}
}

