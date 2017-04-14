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
		return true;
	}
	else
	{
		return false;
	}
}





UProductsSaveGame* ASaveGameManager::GetProductSaveGame()
{
	if (!CurrentProductSaveGame)
	{
		UProductsSaveGame* LoadGameInstance = Cast<UProductsSaveGame>(UGameplayStatics::CreateSaveGameObject(UProductsSaveGame::StaticClass()));
		LoadGameInstance = Cast<UProductsSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		CurrentProductSaveGame = LoadGameInstance;
	}
	return CurrentProductSaveGame;
}

bool ASaveGameManager::ProductsSaveExists()
{
	if (CurrentProductSaveGame)
		return true;
	else
	{
		UProductsSaveGame* saveGame = GetProductSaveGame();
		if (CurrentProductSaveGame)
			return true;
	}

	return false;
}

bool ASaveGameManager::CreateNewProductSaveGameAndSave(FAllProductsData ProductsData)
{

	UE_LOG(LogTemp, Error, TEXT("Trying To Create product save game"));
	UProductsSaveGame* SaveGameInstance = Cast<UProductsSaveGame>(UGameplayStatics::CreateSaveGameObject(UProductsSaveGame::StaticClass()));
	SaveGameInstance->AllProductsData = ProductsData;
	return UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

bool ASaveGameManager::UpdateProductSaveGame(UProductsSaveGame* ToBeSavedGame)
{
	if (UGameplayStatics::SaveGameToSlot(ToBeSavedGame, ToBeSavedGame->SaveSlotName, ToBeSavedGame->UserIndex))
	{
		CurrentProductSaveGame = ToBeSavedGame;
		return true;
	}
	else
		return false;
}
void ASaveGameManager::UpdateProductsIfAny(FAllProductsData ProductsData)
{
	for (FProductData input : ProductsData.Products)
	{
		for (FProductData current : CurrentProductSaveGame->AllProductsData.Products)
		{
			if (input.ProductID == current.ProductID)
			{
				input.DisplayPrice = current.DisplayPrice;
				break;
			}
		}
	}
	CurrentProductSaveGame->AllProductsData = ProductsData;
	UpdateProductSaveGame(CurrentProductSaveGame);
	return;
}

