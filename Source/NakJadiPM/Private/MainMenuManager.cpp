// Fill out your copyright notice in the Description page of Project Settings.

#include "NakJadiPM.h"
#include "MainMenuManager.h"


// Sets default values
AMainMenuManager::AMainMenuManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainMenuManager::BeginPlay()
{
	Super::BeginPlay();
	if (DataManager)
	{
		DataManager->Init();
	}
}

// Called every frame
void AMainMenuManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

bool AMainMenuManager::ChangeToGameLevelIfConditionMet()
{
	//load from save 
	//if exists, load game-> jump to game level 
	//if not create game 
	if(DataManager)
	{
	if (DataManager->GameSaveDataExists())
	{
		UCampaignSaveGame* SavedGame = DataManager->SaveGameManager->GetCampaignSaveGame();
		if (SavedGame->CampaignData.FinishedReported)
			return false;
		else
			return true;
	}
	else
		return false;
	}
	return false;
}

