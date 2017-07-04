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

bool ASaveGameManager::CreateNewProductSaveGameAndSave(FAllProductsData ProductsData, FAllStaffUpgradeData StaffUpgradesData)
{
	UProductsSaveGame* SaveGameInstance = Cast<UProductsSaveGame>(UGameplayStatics::CreateSaveGameObject(UProductsSaveGame::StaticClass()));
	SaveGameInstance->AllProductsData = ProductsData;

	for(FStaffUpgrade upgrade : StaffUpgradesData.StaffUpgrades)
	{
		FStaffUpgradeRecord upgradeRecord = UNJPUtilityFunctionLibrary::CreateStaffUpgradeRecord(upgrade,0);
		SaveGameInstance->staffUpgradeRecords.Add(upgradeRecord);
	}

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

void ASaveGameManager::UpdateStaffUpgradesIfAny(FAllStaffUpgradeData StaffUpgrades)
{
	for (FStaffUpgrade StaffUpgrade : StaffUpgrades.StaffUpgrades)
	{
		bool found = false;
		for (FStaffUpgradeRecord StaffUpgradeRecord : CurrentProductSaveGame->staffUpgradeRecords)
		{
			if (StaffUpgrade.Name == StaffUpgradeRecord.Name)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			CurrentProductSaveGame->staffUpgradeRecords.Add(UNJPUtilityFunctionLibrary::CreateStaffUpgradeRecord(StaffUpgrade,0));
		}
	}
	UpdateProductSaveGame(CurrentProductSaveGame);
	
}


/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save")
UPlayerSettings* CurrentPlayerSettings;
UFUNCTION(BlueprintCallable, Category = "Save")
UPlayerSettings* GetPlayerSettings();
UFUNCTION(BlueprintCallable, Category = "Save")
bool SavedPlayerSettingsExists();
UFUNCTION(BlueprintCallable, Category = "Save")
bool CreateNewPlayerSettingsAndSave();
UFUNCTION(BlueprintCallable, Category = "Save")
bool UpdatePlayerSettingsSave(UPlayerSettings* PlayerSettings);*/

UPlayerSettings* ASaveGameManager::GetPlayerSettings()
{
	if (!CurrentPlayerSettings)
	{
		UPlayerSettings* LoadGameInstance = Cast<UPlayerSettings>(UGameplayStatics::CreateSaveGameObject(UPlayerSettings::StaticClass()));
		LoadGameInstance = Cast<UPlayerSettings>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
		CurrentPlayerSettings = LoadGameInstance;
	}
	return CurrentPlayerSettings;
}

bool ASaveGameManager::SavedPlayerSettingsExists()
{
	if (CurrentPlayerSettings)
		return true;
	else
	{
		UPlayerSettings* saveGame = GetPlayerSettings();
		if (saveGame)
			return true;
	}

	return false;
}

bool ASaveGameManager::CreateNewPlayerSettingsAndSave()
{
	UPlayerSettings* SaveGameInstance = Cast<UPlayerSettings>(UGameplayStatics::CreateSaveGameObject(UPlayerSettings::StaticClass()));
	
	return UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

bool ASaveGameManager::UpdatePlayerSettingsSave(UPlayerSettings* PlayerSettings)
{
	if (UGameplayStatics::SaveGameToSlot(PlayerSettings, PlayerSettings->SaveSlotName, PlayerSettings->UserIndex))
	{
		CurrentPlayerSettings = PlayerSettings;
		return true;
	}
	else
		return false;
}